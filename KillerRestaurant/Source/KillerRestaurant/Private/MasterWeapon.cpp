// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultSceneRoot"));
	SetRootComponent(defaultSceneRoot);

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMesh"));
	weaponMesh->SetupAttachment(defaultSceneRoot);
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

