// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Pistol          UMETA(DisplayName = "Pistol"),
	RifleOrShotgun  UMETA(DisplayName = "Rifle/Shotgun")
};

class KILLERRESTAURANT_API WeaponType
{
public:
	WeaponType();
	~WeaponType();
};
