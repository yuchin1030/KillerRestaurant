// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFireMode : uint8
{
	SemiAuto    UMETA(DisplayName = "SemiAuto"),
	FullAuto	UMETA(DisplayName = "FullAuto"),
	Burst		UMETA(DisplayName = "Burst")
};

class KILLERRESTAURANT_API FireMode
{
public:
	FireMode();
	~FireMode();
};
