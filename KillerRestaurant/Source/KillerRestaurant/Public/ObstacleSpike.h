// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleSpike.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ESpikeState : uint8
{
    Hidden,
    Partial,
    Full
};

UCLASS()
class KILLERRESTAURANT_API AObstacleSpike : public AFloor3ObstacleBase
{
	GENERATED_BODY()
	
public:
	AObstacleSpike();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class USceneComponent* sceneRoot;

    /** Spike Mesh */
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class UStaticMeshComponent* spikeMesh;

    /** Collision for damage */
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class UBoxComponent* boxDamageColl;

    /** Spike movement */
    float curHeight = 0;
    float targetHeight;

    UPROPERTY(EditAnywhere, Category = "MySettings")
    float partialHeight = 30.f;

    UPROPERTY(EditAnywhere, Category = "MySettings")
    float fullHeight = 60.f;

    UPROPERTY(EditAnywhere, Category = "MySettings")
    float speed = 10.f;

    bool bChanged = false;

    /** Current state */
    UPROPERTY(VisibleAnywhere)
    ESpikeState curState;

    /** Tick Ã³¸® */
    void ChangeSpikeState(ESpikeState state);

 


};
