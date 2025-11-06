// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletTrace.generated.h"

UCLASS()
class KILLERRESTAURANT_API ABulletTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USceneComponent* defaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UStaticMeshComponent* staticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UProjectileMovementComponent* ProjectileMovement;

};
