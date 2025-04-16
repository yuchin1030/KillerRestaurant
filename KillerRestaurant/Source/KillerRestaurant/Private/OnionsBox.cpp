// Fill out your copyright notice in the Description page of Project Settings.


#include "OnionsBox.h"
#include "Components/StaticMeshComponent.h"

AOnionsBox::AOnionsBox()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);
}

void AOnionsBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOnionsBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

