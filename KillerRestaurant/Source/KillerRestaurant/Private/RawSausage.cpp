// Fill out your copyright notice in the Description page of Project Settings.


#include "RawSausage.h"
#include "GrilledSausage.h"

ARawSausage::ARawSausage()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);

}

void ARawSausage::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(165, 250, 98));
}

void ARawSausage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


