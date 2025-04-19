// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include "CustomerManager.h"
#include <Kismet/GameplayStatics.h>
#include "CustomerTargetPoint.h"
#include "Components/ArrowComponent.h"
#include <Kismet/KismetMathLibrary.h>

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

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
}

void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	// 음식 주문
	cuM->OrderHotdogMenuCnt();
	customerState = ECustomerState::CHECK;
}

void ACustomer::Wait(float _DeltaTime)
{
	// 주문 후 손님 타이머동안 기다림
}

void ACustomer::Check(float _DeltaTime)
{
	// 모든 음식을 서빙했으면 대화 UI
	if (cuM)
	{
		// 1번 스폰했으면 bSpawnNewCustomer는 true로 되기 때문에 중복으로 안 생김
		if (cuM->bSpawnNewCustomer)
			return;

		cuM->SpawnCustomer();
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
		//새 손님 입장 상태로 바꿔줌
		cuM->SetNewCustomer();
	}
}
