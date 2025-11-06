// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem.h"
#include "KillerRestaurantCharacter.h"
#include "MasterWeapon.h"
#include "WeaponData.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundBase.h"
#include "NiagaraSystem.h"         
#include "NiagaraFunctionLibrary.h"

UWeaponSystem::UWeaponSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UWeaponSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UWeaponSystem::FireCheck(int32 AmmoCount)
{
	if (Weapon_Details.Weapon_AmmoData.CurrentAmmo == 0)
	{
		return false;
	}
	
	Weapon_Details.Weapon_AmmoData.CurrentAmmo -= AmmoCount;

	return true;
		
	
}

void UWeaponSystem::FireFX(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings)
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, Location, FRotator::ZeroRotator, 1, 1, 0, AttenuationSettings, ConcurrencySettings);
}

void UWeaponSystem::MuzzleVFX(UNiagaraSystem* niagara, USceneComponent* AttachToComp)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(niagara, AttachToComp, "None", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
}

void UWeaponSystem::EmptyFX(USoundBase* sound)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), sound, CharacterRef->GetActorLocation());
}

UAnimMontage* UWeaponSystem::FireAnim(UAnimMontage* PistolAnim, UAnimMontage* RifleAnim)
{
	switch (CharacterRef->AnimationState)
	{
	case EAnimationState::Pistol:
		return PistolAnim;
	case EAnimationState::RifleOrShotgun:
		return RifleAnim;
	default:
		break;
	}

	return nullptr;
}

void UWeaponSystem::FireMontage(UAnimMontage* PistolAnim, UAnimMontage* RifleAnim)
{
	CharacterRef->GetMesh()->GetAnimInstance()->Montage_Play(FireAnim(PistolAnim, RifleAnim));
}

