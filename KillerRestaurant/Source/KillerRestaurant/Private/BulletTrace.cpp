// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTrace.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABulletTrace::ABulletTrace()
{
	PrimaryActorTick.bCanEverTick = true;

    defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    SetRootComponent(defaultSceneRoot);

    boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    boxComp->SetupAttachment(defaultSceneRoot);

    staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    staticMesh->SetupAttachment(boxComp); 
    staticMesh->SetRelativeScale3D(FVector(2, 1.5, 1.5));

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 10000;
    ProjectileMovement->MaxSpeed = 10000;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0;
}

void ABulletTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABulletTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

