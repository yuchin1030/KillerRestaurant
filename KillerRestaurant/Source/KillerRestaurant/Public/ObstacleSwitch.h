// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleSwitch.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleSwitch : public AFloor3ObstacleBase
{
	GENERATED_BODY()
	
public:
	AObstacleSwitch();

	virtual void BeginPlay() override;

	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UBoxComponent* boxInteractColl;
};
