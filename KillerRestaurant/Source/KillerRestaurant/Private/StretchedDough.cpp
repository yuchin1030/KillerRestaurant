// Fill out your copyright notice in the Description page of Project Settings.


#include "StretchedDough.h"
#include "Components/StaticMeshComponent.h"

AStretchedDough::AStretchedDough()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);
}

void AStretchedDough::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStretchedDough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

