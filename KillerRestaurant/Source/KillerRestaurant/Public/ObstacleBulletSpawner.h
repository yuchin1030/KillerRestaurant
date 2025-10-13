// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleBulletSpawner.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleBulletSpawner : public AFloor3ObstacleBase
{
	GENERATED_BODY()
	
public:
    AObstacleBulletSpawner();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class USceneComponent* sceneRoot;

    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    class UStaticMeshComponent* spawnerMesh;

    // 총알 클래스
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    TSubclassOf<class AObstacleBulletProjectile> bulletClass;

    // 날라오는 총알 스폰 간격
    UPROPERTY(EditAnywhere, Category = "MySettings")
    float spawnInterval = 3.f;

    // 스폰 방향(오,왼,정면,후면)
    UPROPERTY(EditAnywhere, Category = "MySettings")
    FRotator spawnRot;

    UFUNCTION()
    void SpawnBullet();
};
