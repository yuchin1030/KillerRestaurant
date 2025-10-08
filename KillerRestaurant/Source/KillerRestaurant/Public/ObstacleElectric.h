// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor3ObstacleBase.h"
#include "ObstacleElectric.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AObstacleElectric : public AFloor3ObstacleBase, public ICanInteract
{
	GENERATED_BODY()
	
public:
	AObstacleElectric();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class USceneComponent* sceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UBoxComponent* boxDamageColl;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UBoxComponent* boxInteractColl;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UStaticMeshComponent* smComp;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UNiagaraComponent* VFX_electric;

	// 블프상 Instance Editable과 같은 기능을 하려면 EditAnywhere로 해야 한다.
	UPROPERTY(EditAnywhere, Category = "MySettings")
	bool bRotateRight;

	// CanInteract 인터페이스 오버라이드 함수
	UFUNCTION()
	virtual void RotateTarget() override;
};
