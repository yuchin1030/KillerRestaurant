// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"
#include "Customer.h"
#include <Kismet/GameplayStatics.h>

ACustomerManager::ACustomerManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerManager::BeginPlay()
{
	Super::BeginPlay();
	
	currentCustomer = Cast<ACustomer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomer::StaticClass()));
}

void ACustomerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomerManager::SpawnCustomer()
{
	FActorSpawnParameters params;
	nextCustomer = GetWorld()->SpawnActor<ACustomer>(customer_bp, customerStartLoc, FRotator::ZeroRotator, params);

	if (nextCustomer)
	{//********************************
		//currentCustomer->customerState = ECustomerState::EXIT;
		
		// ���� Check(��ȭUI) �����̱� ������ IDLE �� ���
		nextCustomer->customerState = ECustomerState::IDLE;

		// ���� �մ��� ���� ������ �� ������ �� �մ� ���� ���·� �ٲ���
		if (currentCustomer->customerState == ECustomerState::EXIT)
		{
			nextCustomer->customerState = ECustomerState::ENTRY;
			
			
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nextCustomer is null"));
	}
}

