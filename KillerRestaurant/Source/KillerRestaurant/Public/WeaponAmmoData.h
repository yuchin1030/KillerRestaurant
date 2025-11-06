// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAmmoData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeapon_AmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentAmmo = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxAmmo = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ClipAmmo = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DifferentAmmo = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AmmoCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ShortGunTrace = 0;
};
