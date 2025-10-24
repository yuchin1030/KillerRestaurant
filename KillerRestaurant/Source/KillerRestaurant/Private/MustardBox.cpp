// Fill out your copyright notice in the Description page of Project Settings.


#include "MustardBox.h"
#include "Components/StaticMeshComponent.h"

AMustardBox::AMustardBox()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);

	smComp->SetRelativeScale3D(FVector(2.5));

}

void AMustardBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMustardBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

