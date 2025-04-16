// Fill out your copyright notice in the Description page of Project Settings.


#include "KetchupBox.h"
#include "Components/StaticMeshComponent.h"

AKetchupBox::AKetchupBox()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);
}

void AKetchupBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKetchupBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

