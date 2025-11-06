// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponType.h"
#include "FireMode.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    /** ================== Weapon Details ================== */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Details")
    FString WeaponName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Details")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Details")
    TSubclassOf<class AMasterWeapon> WeaponClass;


    /** ================== Fire Mode Data ================== */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Fire Mode")
    EFireMode FireMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Fire Mode")
    int32 BurstAmount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Fire Mode")
    float FireRate = 0.1f;


    /** ================== Ballistics ================== */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ballistics")
    float BulletSpread = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ballistics")
    float Damage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ballistics")
    float MaxRange = 5000.f;


    /** ================== Animations ================== */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Animations")
    FVector LeftHandIKOffset = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Animations")
    UAnimMontage* BodyFireMontage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Animations")
    UAnimMontage* WeaponFireMontage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Animations")
    UAnimMontage* BodyReloadMontage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Animations")
    UAnimMontage* WeaponReloadMontage = nullptr;


    /** ================== UI ================== */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|UI")
    UTexture2D* WeaponUITexture = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|UI")
    TSubclassOf<UUserWidget> WeaponUI = nullptr;


    /** ================== Audio ================== */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
    USoundBase* FireSound = nullptr;
};
