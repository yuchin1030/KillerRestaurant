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
	// ���տ��� �̸� ���(���� �մ԰� ��ȭ UI�ִµ��� �̸� �����Ͽ� Idle���� - ���� �մ� Exit �����϶� Entry�� �ٲ���)
	customerState = ECustomerState::ENTRY;
}

void ACustomer::Entry(float _DeltaTime)
{
	// ī���� �ձ��� �̵�
	UE_LOG(LogTemp, Warning, TEXT("Entry"));

	if (A_customerOrderTargetLoc)
	{
		AAIController* AIController = Cast<AAIController>(GetController());

		if (AIController)
		{
			//  ī���� �ձ��� �̵�
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, A_customerOrderTargetLoc->GetActorLocation());

			// ���� �� ������ �մ��� ������ �ٶ󺸰� ȸ��
			if (FVector::Dist(GetActorLocation(), A_customerOrderTargetLoc->GetActorLocation()) < 100.f)
			{
				FRotator newRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 180, 0), _DeltaTime, 90); // 180 : RotationSpeed

				SetActorRotation(newRot);

				if (GetActorRotation().Equals(FRotator(0, 180, 0), 1.0f)) // ��� ���� 1��
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
	// ���� �ֹ�
	
}

void ACustomer::Wait(float _DeltaTime)
{
	// �ֹ� �� �մ� Ÿ�̸ӵ��� ��ٸ�
}

void ACustomer::Check(float _DeltaTime)
{
	// ��� ������ ���������� ��ȭ UI
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
	// ����
}

