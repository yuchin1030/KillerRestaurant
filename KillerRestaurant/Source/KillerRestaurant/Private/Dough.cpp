// Fill out your copyright notice in the Description page of Project Settings.


#include "Dough.h"
#include "Components/StaticMeshComponent.h"
ADough::ADough()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));

	smComp->OnClicked.AddDynamic(this, &ADough::OnClicked);
}

void ADough::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADough::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
    if (TargetLocationActor)
    {
        FVector TargetLocation = TargetLocationActor->GetActorLocation();
        SetActorLocation(TargetLocation);

        UE_LOG(LogTemp, Warning, TEXT("Click"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TargetLocationActor is null"));
    }

    //UE_LOG(LogTemp, Warning, TEXT("Click!"));
}

