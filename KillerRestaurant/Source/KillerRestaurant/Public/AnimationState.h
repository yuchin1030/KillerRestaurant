// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAnimationState : uint8
{
    Unarmed         UMETA(DisplayName = "Unarmed"),
    Pistol          UMETA(DisplayName = "Pistol"),
    RifleOrShotgun  UMETA(DisplayName = "Rifle/Shotgun")
};

class KILLERRESTAURANT_API AnimationState
{
public:
	AnimationState();
	~AnimationState();
};
