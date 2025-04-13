// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyRestaurGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AMyRestaurGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class AKillerRestaurantCharacter* player;
};
