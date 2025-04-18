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
	
	cm = Cast<ACustomerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerManager::StaticClass()));
	customerTargetPoint = Cast<ACustomerTargetPoint>(A_customerTargetLoc);

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
	// ���տ��� �̸� ���(���� �մ԰� ��ȭ UI�ִµ��� �̸� �����Ͽ� Idle���� - ���� �մ� Exit �����϶� Entry�� �ٲ���)
	customerState = ECustomerState::ENTRY;
}

void ACustomer::Entry(float _DeltaTime)
{
	// ī���� �ձ��� �̵�
	UE_LOG(LogTemp, Warning, TEXT("Entry"));

	if (A_customerTargetLoc)
	{
		if (AIController)
		{
			if (customerTargetPoint)
			{
				//  ī���� �ձ��� �̵�
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, customerTargetPoint->orderTargetPoint->GetComponentLocation());

				// ���� �� ������ �մ��� ������ �ٶ󺸰� ȸ��
				if (FVector::Dist(GetActorLocation(), customerTargetPoint->orderTargetPoint->GetComponentLocation()) < 100.f)
				{
					FRotator newRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 180, 0), _DeltaTime, 90); // 180 : RotationSpeed

					SetActorRotation(newRot);

					if (GetActorRotation().Equals(FRotator(0, 180, 0), 1.0f)) // ��� ���� 1��
					{
						customerState = ECustomerState::CHECK;
					}
				}


			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("customerTargetPoint is null"));
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

void ACustomer::Exit(float _DeltaTime)
{
	// ����
	if (customerTargetPoint)
	{
		if (!bSelectExitLocRot)
		{
			// �� �� ���� �������� �����ϸ� �� �̻� ���� ���ϰ�
			bSelectExitLocRot = true;

			// ������ �����Ұ���, ������ �����Ұ��� �������� ��
			bExitToFront = UKismetMathLibrary::RandomBoolWithWeight(0.5);
		}

		// targetRot, targetLoc (��ǥ�ϴ� ȸ������, �մ��� �����ϱ���� �����ؾ� �ϴ� ��ġ)
		// ������ �����ϸ� FRotator(0) (�÷��̾� ���忡�� �޸�� ����) ȸ�� ��Ų �� targetPoint ���� �̵�
		if (bExitToFront)
		{
			ExitRotateAndMove(FRotator(0), customerTargetPoint->exitFrontTargetPint->GetComponentLocation(), _DeltaTime);
		}
		// ������ �����ϸ� FRotator(90) (�÷��̾� ���忡�� ����� ����) ȸ�� ��Ų �� targetPoint ���� �̵�
		else
		{
			ExitRotateAndMove(FRotator(0, 90, 0), customerTargetPoint->exitRightTargetPoint->GetComponentLocation(), _DeltaTime);
		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("customerTargetPoint is null"));
	}
}


void ACustomer::ExitRotateAndMove(FRotator exitTargetRot, FVector exitTargetLoc, float DeltaTime)
{
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), exitTargetRot, DeltaTime, 90); // 90 : RotationSpeed

	SetActorRotation(newRot);

	if (GetActorRotation().Equals(exitTargetRot, 1.0f)) // ��� ���� 1��
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, exitTargetLoc);

	// �մ��� ���� ��ġ���� ���� �� ������
	if (FVector::Dist(GetActorLocation(), exitTargetLoc) < 100.f)
	{
		cm->currentCustomer = cm->nextCustomer;
		cm->nextCustomer = nullptr;
		// this->Destroy(); *****************************
	}
}
