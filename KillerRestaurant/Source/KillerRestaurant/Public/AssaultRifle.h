// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterWeapon.h"
#include "AssaultRifle.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AAssaultRifle : public AMasterWeapon
{
	GENERATED_BODY()
	
public:
	AAssaultRifle();

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* Muzzle;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USoundBase* EmptySound;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class UCameraShakeBase> ShakeClass;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USoundAttenuation* AttenuationSettings;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USoundConcurrency* ConcurrencySettings;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UNiagaraSystem* niagara;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ABulletTrace> BulletTraceClass;

	virtual void Fire() override;

	void FireFX();

	void FireBlankTracer();

	FVector2D RandomPointInCircle(float radius);

	void FireGun(const FHitResult& HitResult, bool bReturnHit);

};
