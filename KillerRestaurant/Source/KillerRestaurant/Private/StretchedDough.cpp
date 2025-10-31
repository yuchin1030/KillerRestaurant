// Fill out your copyright notice in the Description page of Project Settings.


#include "StretchedDough.h"
#include "Components/StaticMeshComponent.h"

AStretchedDough::AStretchedDough()
{
	PrimaryActorTick.bCanEverTick = true;

	sm_bread = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_bread"));
	SetRootComponent(sm_bread);

	sm_sausage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_sausage"));
	sm_pickles = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_pickles"));
	sm_onions = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_onions"));
	sm_ketchup = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_ketchup"));
	sm_mustard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_mustard"));

	sm_sausage->SetupAttachment(sm_bread);
	sm_pickles->SetupAttachment(sm_bread);
	sm_onions->SetupAttachment(sm_bread);
	sm_ketchup->SetupAttachment(sm_bread);
	sm_mustard->SetupAttachment(sm_bread);

	sm_sausage->SetVisibility(false);
	sm_pickles->SetVisibility(false);
	sm_onions->SetVisibility(false);
	sm_ketchup->SetVisibility(false);
	sm_mustard->SetVisibility(false);

	sm_sausage->SetRelativeLocation(FVector(-8, -18, -11));
	sm_sausage->SetRelativeScale3D(FVector(-1, 0, 2));

	sm_pickles->SetRelativeLocation(FVector(2, -3, 30));

	sm_onions->SetRelativeLocation(FVector(-8, -18, -11));
	sm_onions->SetRelativeScale3D(FVector(1.25f));

	sm_ketchup->SetRelativeLocation(FVector(2, 0, 5));
	sm_ketchup->SetRelativeScale3D(FVector(1.5, 1.4, 1));

	sm_mustard->SetRelativeLocation(FVector(-2, 0, 4));
	sm_mustard->SetRelativeScale3D(FVector(1.5, 1.4, 1));


}

void AStretchedDough::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStretchedDough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStretchedDough::SetCurBreadLocIndex(int32 index)
{
	curBreadLocIndex = index;
}

