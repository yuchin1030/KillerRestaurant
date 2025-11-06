// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapon.generated.h"

UCLASS()
class KILLERRESTAURANT_API AMasterWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* defaultSceneRoot;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USkeletalMeshComponent* weaponMesh;

};
