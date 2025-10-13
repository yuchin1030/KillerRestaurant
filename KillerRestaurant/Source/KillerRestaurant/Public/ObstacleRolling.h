// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleRolling.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleRolling : public AFloor3ObstacleBase
{
	GENERATED_BODY()
public:
	AObstacleRolling();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* sceneRoot;

	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* caps_RollingDamageColl;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* rollingMeshComp;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* endMarker;

	// 시작과 끝 지점 (에디터에서 배치 가능)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	FVector startPoint;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FVector endPoint;

	// 이동 속도 관련
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float moveSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float rotateRadius = 50;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float slowDownDist = 200.f;

	// 멈췄을 때 잠시 대기 시간
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float stopDelay = 3; 

private:
	bool bMovingToEnd = true;
	float currentSpeed = 0.f;
	float targetSpeed = 0.f;
	float accelInterpSpeed = 2.5f;
	bool bWaiting = false;

	FTimerHandle WaitTimerHandle;

	void ToggleDirection();
};
