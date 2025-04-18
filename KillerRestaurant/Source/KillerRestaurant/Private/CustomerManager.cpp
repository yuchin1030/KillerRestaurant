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
		
		// 아직 Check(대화UI) 상태이기 때문에 IDLE 로 대기
		nextCustomer->customerState = ECustomerState::IDLE;

		// 이전 손님이 퇴장 상태일 때 스폰한 새 손님 입장 상태로 바꿔줌
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

