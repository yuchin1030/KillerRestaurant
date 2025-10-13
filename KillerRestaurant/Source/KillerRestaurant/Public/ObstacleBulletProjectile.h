// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleBulletProjectile.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleBulletProjectile : public AFloor3ObstacleBase
{
	GENERATED_BODY()

public:
	AObstacleBulletProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class USceneComponent* sceneRoot;

    /** Spike Mesh */
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class UStaticMeshComponent* bulletMesh;

    /** Collision for damage */
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class USphereComponent* sph_BulletDamageColl;

    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class UProjectileMovementComponent* projectileMovement;

    // 몇 초 후에 Destroy
    UPROPERTY(EditAnywhere, Category = "MySettings")
    float lifeTime = 1.f;

    UPROPERTY(EditAnywhere, Category = "MySettings")
    float projectileInitSpeed = 2000.f;

    UPROPERTY(EditAnywhere, Category = "MySettings")
    float projectileMaxSpeed = 2000.f;

    UFUNCTION()
    void DestroyProjectile();
};
