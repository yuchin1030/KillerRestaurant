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

void AGrilledSausage::Grill(int32 index)
{
	int32 _index = index;

	FTimerHandle grillTimerHdl;
	GetWorld()->GetTimerManager().SetTimer(grillTimerHdl, [&]() {

		isGrilled = true;
		UE_LOG(LogTemp, Warning, TEXT("sausage grilled!"));
		SetActorRotation(FRotator(0,90,0));

		/*isGrilled[_index] = true;
		UE_LOG(LogTemp, Warning, TEXT("sausage%d grilled!"), _index);
		UE_LOG(LogTemp, Warning, TEXT("isGrilled[] : %d %d %d"), isGrilled[0], isGrilled[1], isGrilled[2]);*/

		FTimerHandle burnTimerHdl;
		GetWorld()->GetTimerManager().SetTimer(burnTimerHdl, [&]() {

			UE_LOG(LogTemp, Warning, TEXT("sausage burned!"));
			SetActorRotation(FRotator(0, 90, 0));

			//UE_LOG(LogTemp, Warning, TEXT("sausage%d burned!"), index);
		}, 7.0f, false);
	}, 7.0f, false);
}

