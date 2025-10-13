// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleFalling.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleFalling : public AFloor3ObstacleBase
{
	GENERATED_BODY()
	
public:
    AObstacleFalling();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UGeometryCollectionComponent* destructibleMeshComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class USphereComponent* sph_DamageColl;

    // Hit ¿Ã∫•∆Æ
    /*UFUNCTION()
    void OnDamageHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);*/
};
