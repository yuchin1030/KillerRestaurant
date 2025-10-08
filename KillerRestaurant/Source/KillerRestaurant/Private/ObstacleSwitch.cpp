// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSwitch.h"
#include "Components/BoxComponent.h"

AObstacleSwitch::AObstacleSwitch()
{
	PrimaryActorTick.bCanEverTick = true;

	boxInteractColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxInteractColl"));
}

void AObstacleSwitch::BeginPlay()
{
	Super::BeginPlay();

	boxInteractColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapInteract);
}
