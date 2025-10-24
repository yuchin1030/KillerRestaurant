// Fill out your copyright notice in the Description page of Project Settings.


#include "Dough.h"
#include "Components/StaticMeshComponent.h"
#include "StretchedDough.h"

ADough::ADough()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
    SetRootComponent(smComp);
}

void ADough::BeginPlay()
{
	Super::BeginPlay();
    SetActorLocation(FVector(-18, -366, 97));
}

void ADough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}