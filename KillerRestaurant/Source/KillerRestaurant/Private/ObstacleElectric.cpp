// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleElectric.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "CanInteract.h"

AObstacleElectric::AObstacleElectric()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
	boxDamageColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxDamageColl"));
	boxInteractColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxInteractColl"));
	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	VFX_electric = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX_electric"));

	SetRootComponent(sceneRoot);
	boxDamageColl->SetupAttachment(sceneRoot);
	boxInteractColl->SetupAttachment(sceneRoot);
	VFX_electric->SetupAttachment(boxDamageColl);
	smComp->SetupAttachment(boxInteractColl);

	boxDamageColl->SetRelativeLocation(FVector(180, 0, 50));
	boxDamageColl->SetBoxExtent(FVector(120, 20, 32));
	boxInteractColl->SetBoxExtent(FVector(42, 42, 100));
	VFX_electric->SetRelativeLocation(FVector(-150, 0, 0));
	smComp->SetRelativeScale3D(FVector(0.5, 0.5, 2));
}

void AObstacleElectric::BeginPlay()
{
	Super::BeginPlay();

	boxDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);
	boxInteractColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapInteract);
}

void AObstacleElectric::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacleElectric::RotateTarget()
{
	if (bRotateRight)
	{
		UE_LOG(LogTemp, Warning, TEXT("RotateRight"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RotateLeft"));
	}
}
