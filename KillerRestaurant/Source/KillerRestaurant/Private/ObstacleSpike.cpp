// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpike.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AObstacleSpike::AObstacleSpike()
{
    PrimaryActorTick.bCanEverTick = true;

    sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
    SetRootComponent(sceneRoot);

    spikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spikeMesh"));
    spikeMesh->SetupAttachment(sceneRoot);

    boxDamageColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxDamageColl"));
    boxDamageColl->SetupAttachment(spikeMesh);

    curState = ESpikeState::Hidden;

    boxDamageColl->SetCollisionProfileName(TEXT("Obstacle"));
    spikeMesh->SetCollisionProfileName(TEXT("Obstacle"));
}

void AObstacleSpike::BeginPlay()
{
    Super::BeginPlay();

    boxDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);

    ChangeSpikeState(curState);
}

void AObstacleSpike::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bChanged)
    {
        curHeight = FMath::FInterpTo(curHeight, targetHeight, DeltaTime, speed);
        spikeMesh->SetRelativeLocation(FVector(0, 0, curHeight));
        
        if (FMath::IsNearlyEqual(curHeight, targetHeight, 1.f))
        {
            bChanged = false;

            FTimerHandle stateHdl;
            GetWorldTimerManager().SetTimer(stateHdl, [&]() {
                ChangeSpikeState(curState);
            }, 0.1f, false);
        }
    }

}

void AObstacleSpike::ChangeSpikeState(ESpikeState state)
{
    bChanged = true;

    if (state == ESpikeState::Hidden)
    {
        curState = ESpikeState::Partial;
        targetHeight = partialHeight;
        boxDamageColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    else if (state == ESpikeState::Partial)
    {
        curState = ESpikeState::Full;
        targetHeight = fullHeight;
        boxDamageColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    else
    {
        curState = ESpikeState::Hidden;
        targetHeight = 0;
        boxDamageColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

   
}
