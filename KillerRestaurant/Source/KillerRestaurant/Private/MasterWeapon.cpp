// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponSystem.h"
#include "WeaponData.h"
#include "KillerRestaurantCharacter.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>

AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultSceneRoot"));
	SetRootComponent(defaultSceneRoot);

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMesh"));
	weaponMesh->SetupAttachment(defaultSceneRoot);

	WeaponSystem = CreateDefaultSubobject<UWeaponSystem>(TEXT("WeaponSystem"));
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponSystem->CharacterRef = Cast<AKillerRestaurantCharacter>(GetAttachParentActor());
}

void AMasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterWeapon::Fire()
{

}

