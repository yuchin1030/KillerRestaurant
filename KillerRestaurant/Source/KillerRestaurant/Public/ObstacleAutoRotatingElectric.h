// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleAutoRotatingElectric.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleAutoRotatingElectric : public AFloor3ObstacleBase
{
	GENERATED_BODY()
	
public:
	AObstacleAutoRotatingElectric();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USceneComponent* sceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UBoxComponent* boxDamageColl;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UStaticMeshComponent* smComp;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UNiagaraComponent* VFX_electric;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	bool bAutoRotateRight;

	// 회전하는 방향
	FRotator targetRot;

	// 현재 회전하고 있는가
	bool bRotating;
	float rotateElapsedTime = 0;

	// 회전 시간
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float rotateDuration = 0.5f;

	// 회전되는 간격
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float rotateInterval = 3;

	UFUNCTION()
	void StartRotation();
	
};
