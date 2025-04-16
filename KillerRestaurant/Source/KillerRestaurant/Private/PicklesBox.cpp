// Fill out your copyright notice in the Description page of Project Settings.


#include "PicklesBox.h"
#include "Components/StaticMeshComponent.h"

APicklesBox::APicklesBox()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);
}

void APicklesBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void APicklesBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

