// Fill out your copyright notice in the Description page of Project Settings.


#include "GrilledSausage.h"
#include "Components/StaticMeshComponent.h"

AGrilledSausage::AGrilledSausage()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);
}

void AGrilledSausage::BeginPlay()
{
	Super::BeginPlay();
	
	//isGrilled.Init(false, 3);
}

void AGrilledSausage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrilledSausage::Grill()
{
	FTimerHandle grillTimerHdl;
	GetWorld()->GetTimerManager().SetTimer(grillTimerHdl, [&]() {

		isGrilled = true;
		UE_LOG(LogTemp, Warning, TEXT("sausage grilled!"));
		SetActorRotation(FRotator(0,90,0));

		FTimerHandle burnTimerHdl;
		GetWorld()->GetTimerManager().SetTimer(burnTimerHdl, [&]() {

			isBurned = true;
			UE_LOG(LogTemp, Warning, TEXT("sausage burned!"));
			SetActorRotation(FRotator(0));

		}, 3.0f, false);
	}, 3.0f, false);
}
