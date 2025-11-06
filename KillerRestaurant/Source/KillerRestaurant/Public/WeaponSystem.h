// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationState.h"
#include "WeaponDetails.h"
#include "WeaponSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KILLERRESTAURANT_API UWeaponSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponSystem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class AKillerRestaurantCharacter* CharacterRef;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class AMasterWeapon> MasterWeaponClass;
		
	UPROPERTY(EditAnywhere, Category = "MySettings")
	EAnimationState WeaponType;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FWeaponDetails Weapon_Details;

	bool bIsDryAmmo;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UWeaponData* PistolData;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UWeaponData* RifleData;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UUserWidget* crosshairWidget;

	UFUNCTION()
	bool FireCheck(int32 AmmoCount);

	UFUNCTION()
	void FireFX(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings);

	UFUNCTION()
	void MuzzleVFX(UNiagaraSystem* niagara, USceneComponent* AttachToComp);

	UFUNCTION()
	void EmptyFX(USoundBase* sound);

	UAnimMontage* FireAnim(UAnimMontage* PistolAnim, UAnimMontage* RifleAnim);

	UFUNCTION()
	void FireMontage(UAnimMontage* PistolAnim, UAnimMontage* RifleAnim);
};
