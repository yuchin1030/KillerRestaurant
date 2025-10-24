// Fill out your copyright notice in the Description page of Project Settings.


#include "ServingBell.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AServingBell::AServingBell()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	sm_FirstBell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_FirstBell"));
	sm_SecondBell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_SecondBell"));
	sm_ThirdBell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_ThirdBell"));

	SetRootComponent(sceneComp);
	sm_FirstBell->SetupAttachment(sceneComp);
	sm_SecondBell->SetupAttachment(sceneComp);
	sm_ThirdBell->SetupAttachment(sceneComp);

	sm_FirstBell->SetRelativeLocation(FVector(0, -200, 0));
	sm_FirstBell->SetRelativeScale3D(FVector(2));

	sm_SecondBell->SetRelativeLocation(FVector(0, 0, 0));
	sm_SecondBell->SetRelativeScale3D(FVector(2));

	sm_ThirdBell->SetRelativeLocation(FVector(0, 200, 0));
	sm_ThirdBell->SetRelativeScale3D(FVector(2));
}

void AServingBell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AServingBell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

