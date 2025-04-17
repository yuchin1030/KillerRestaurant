// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include "CustomerManager.h"
#include <Kismet/GameplayStatics.h>

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	
	cm = Cast<ACustomerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerManager::StaticClass()));
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
		Exit();
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
	UE_LOG(LogTemp, Warning, TEXT("Entry"));

	if (A_customerOrderTargetLoc)
	{
		AAIController* AIController = Cast<AAIController>(GetController());

		if (AIController)
		{
			//  카운터 앞까지 이동
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, A_customerOrderTargetLoc->GetActorLocation());

			// 거의 다 왔으면 손님이 정면을 바라보게 회전
			if (FVector::Dist(GetActorLocation(), A_customerOrderTargetLoc->GetActorLocation()) < 100.f)
			{
				FRotator newRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 180, 0), _DeltaTime, 90); // 180 : RotationSpeed

				SetActorRotation(newRot);

				if (GetActorRotation().Equals(FRotator(0, 180, 0), 1.0f)) // 허용 오차 1도
				{
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
		UE_LOG(LogTemp, Warning, TEXT("A_customerOrderTargetLoc is null"));
	}
	
}

void ACustomer::Order()
{
	// 음식 주문
	
}

void ACustomer::Wait(float _DeltaTime)
{
	// 주문 후 손님 타이머동안 기다림
}

void ACustomer::Check(float _DeltaTime)
{
	// 모든 음식을 서빙했으면 대화 UI
	if (cm)
	{
		cm->SpawnCustomer();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("cm is null"));
	}
}

void ACustomer::Exit()
{
	// 퇴장
}

