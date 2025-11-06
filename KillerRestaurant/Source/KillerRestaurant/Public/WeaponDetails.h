// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAmmoData.h"
#include "WeaponDetails.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	FWeapon_AmmoData Weapon_AmmoData;
};
