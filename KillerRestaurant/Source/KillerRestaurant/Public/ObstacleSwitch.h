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

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch")
    //int32 SwitchGroupID = 0; // 소속 그룹 ID

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch")
    //float ActiveTime = 5.f;

    //UPROPERTY(BlueprintReadOnly)
    //bool bIsActive = false;

};
