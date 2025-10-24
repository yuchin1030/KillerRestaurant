// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include "CustomerManager.h"
#include <Kismet/GameplayStatics.h>
#include "CustomerTargetPoint.h"
#include "Components/ArrowComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "Components/WidgetComponent.h"
#include "MyRestaurGameModeBase.h"
#include "CustomerDialogueWidget.h"
#include <CustomerDialougeDataAsset.h>

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	orderWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("orderWidgetComp"));
	orderWidgetComp->SetupAttachment(GetMesh());
	// orderWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // 또는 World
	orderWidgetComp->SetDrawSize(FVector2D(300, 300)); // 위젯 크기 설정
	orderWidgetComp->SetVisibility(false); // 처음엔 안 보이게

	
}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	
	cuM = Cast<ACustomerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerManager::StaticClass()));

	//  컨트롤러는 월드에 스폰된 직후 바로 생기는 게 아니라, 약간의 시간 차를 두고 자동으로 생성.
	// 즉, BeginPlay()나 Tick()의 첫 프레임 등에서는 Controller가 아직 null일 수 있음
	// 따라서 AIController 수동 생성
	SpawnDefaultController();

	AIController = Cast<AAIController>(GetController());

	gm = Cast<AMyRestaurGameModeBase>(GetWorld()->GetAuthGameMode());
}

void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!cuM->bCanPlaying)
		return;

	switch (customerState)
	{
	case ECustomerState::IDLE:
		Idle();
		break;
	case ECustomerState::ENTRY:
		Entry(DeltaTime);
		break;
	case ECustomerState::ORDER:
		Order();
		break;
	case ECustomerState::WAIT:
		Wait(DeltaTime);
		break;
	case ECustomerState::CHECK:
		Check(DeltaTime);
		break;
	case ECustomerState::EXIT:
		Exit(DeltaTime);
		break;
	}
}

void ACustomer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomer::Idle()
{
	// 문앞에서 미리 대기(이전 손님과 대화 UI있는동안 미리 스폰하여 Idle상태 - 다음 손님 Exit 상태일때 Entry로 바꿔줌)
	customerState = ECustomerState::ENTRY;
}

void ACustomer::Entry(float _DeltaTime)
{
	// 카운터 앞까지 이동
	if (cuM->customerTargetPoint)
	{
		if (AIController)
		{
			//  카운터 앞까지 이동
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, cuM->customerTargetPoint->orderTargetPoint->GetComponentLocation());

			// 주문지점까지 거의 다 왔으면 손님이 정면(카운터)을 바라보게 회전
			if (FVector::Dist(GetActorLocation(), cuM->customerTargetPoint->orderTargetPoint->GetComponentLocation()) < 100.f)
			{
				FRotator newRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 180, 0), _DeltaTime, 90); // 180 : RotationSpeed

				SetActorRotation(newRot);

				// 거의 다 회전했으면
				if (GetActorRotation().Equals(FRotator(0, 180, 0), 1.0f)) // 허용 오차 1도
				{
					// 주문하기
					customerState = ECustomerState::ORDER;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AIController is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("customerTargetPoint is null"));
	}
	
}

void ACustomer::Order()
{
	if (cuM->bOrdered)
		return;

	// 음식 주문
	cuM->OrderHotdogMenuCnt();

	orderWidgetComp->SetVisibility(true);
}

void ACustomer::Wait(float _DeltaTime)
{
	cuM->SetPlayerCameraView(true);
	orderWidgetComp->SetVisibility(false);

	// 주문 후 손님 타이머동안 기다림
	currentTime += _DeltaTime;

	// 서빙 다 못했는데 만족도 0 되면 (서빙 다 했을 때 CHECK 로 사태 전환시키는건 Character, CookManager 에 있음
	if (totalSatisfaction <= 0)
	{
		// 자동으로 대화 UI 하게끔 상태 변경
		customerState = ECustomerState::CHECK;
	}
	else if (currentTime > decreaseInterval)
	{
		totalSatisfaction--;
		currentTime = 0;

		UE_LOG(LogTemp, Warning, TEXT("Customer satisfaction: %f"), totalSatisfaction);
	}

}

void ACustomer::Check(float _DeltaTime)
{
	cuM->SetPlayerCameraView(false);

	// 손님 만족도가 0 됐거나 모든 음식을 서빙했으면 
	if (cuM)
	{
		// 1번 스폰했으면 bSpawnNewCustomer는 true로 되기 때문에 중복으로 안 생김
		if (cuM->bSpawnNewCustomer)
			return;

		// 정산
		cuM->CalculateReward(totalSatisfaction);

		// 대화 UI 및 
		FClueDialogueEntry dialogueResult = cuM->GetCustomerDialogue(totalSatisfaction);
		UE_LOG(LogTemp, Warning, TEXT("dialogue : %s"), *dialogueResult.Dialogue);

		cuM->dialogueUI->SetDialogueUI(FText::GetEmpty(), dialogueResult.Dialogue, dialogueResult.Choices, TArray<float>());
		cuM->dialogueUI->SetVisibility(ESlateVisibility::Visible);

		// 영업시간 종료가 아닐 경우에만
		if (!gm->bClosingTime)
			// 새 손님 Idle 상태 스폰 (OrderedHotdogs, allTotalPrice 초기화)
			cuM->SpawnCustomer();
		else
			customerState = ECustomerState::EXIT;	// 대화창 UI 구현되면 수정하기

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("cuM is null"));
	}
}

void ACustomer::Exit(float _DeltaTime)
{
	// 퇴장
	if (cuM->customerTargetPoint)
	{
		if (!bSelectExitLocRot)
		{
			// 한 번 어디로 퇴장할지 선택하면 더 이상 선택 못하게
			bSelectExitLocRot = true;

			// 앞으로 퇴장할건지, 옆으로 퇴장할건지 랜덤으로 고름
			bExitToFront = UKismetMathLibrary::RandomBoolWithWeight(0.5);
		}

		// targetRot, targetLoc (목표하는 회전방향, 손님이 퇴장하기까지 도달해야 하는 위치)
		// 앞으로 퇴장하면 FRotator(0) (플레이어 입장에서 뒷모습 보임) 회전 시킨 후 targetPoint 까지 이동
		if (bExitToFront)
		{
			exitTargetLoc = cuM->customerTargetPoint->exitFrontTargetPint->GetComponentLocation();

			ExitRotateAndMove(FRotator(0), exitTargetLoc, _DeltaTime);
		}
		// 옆으로 퇴장하면 FRotator(90) (플레이어 입장에서 옆모습 보임) 회전 시킨 후 targetPoint 까지 이동
		else
		{
			exitTargetLoc = cuM->customerTargetPoint->exitRightTargetPoint->GetComponentLocation();

			ExitRotateAndMove(FRotator(0, 90, 0), exitTargetLoc, _DeltaTime);
		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("customerTargetPoint is null"));
	}

}

void ACustomer::ExitRotateAndMove(FRotator exitTargetRot, FVector _exitTargetLoc, float DeltaTime)
{
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), exitTargetRot, DeltaTime, 90); // 90 : RotationSpeed

	SetActorRotation(newRot);

	if (GetActorRotation().Equals(exitTargetRot, 1.0f)) // 허용 오차 1도
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, _exitTargetLoc);

	// 손님이 퇴장 위치까지 거의 다 왔으면
	if (FVector::Dist(GetActorLocation(), _exitTargetLoc) < 100.f)
	{
		// 영업시간 종료가 아닐 경우에만
		if (!gm->bClosingTime)
			//새 손님 입장 상태로 바꿔줌
			cuM->SetNewCustomer();
		else
			cuM->bCanPlaying = false;
	}
}
