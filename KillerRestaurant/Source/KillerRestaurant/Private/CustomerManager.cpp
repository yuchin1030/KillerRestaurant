// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"
#include "Customer.h"

ACustomerManager::ACustomerManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerManager::BeginPlay()
{
	Super::BeginPlay();
}

void ACustomerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomerManager::SpawnCustomer()
{
	FActorSpawnParameters params;
	ACustomer* customer = GetWorld()->SpawnActor<ACustomer>(customer_bp, customerStartLoc, FRotator::ZeroRotator, params);

	// ���� Check(��ȭUI) �����̱� ������ IDLE �� ���
	customer->customerState = ECustomerState::IDLE;
}

