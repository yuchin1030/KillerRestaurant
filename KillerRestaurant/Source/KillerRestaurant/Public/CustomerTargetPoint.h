// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomerTargetPoint.generated.h"

UCLASS()
class KILLERRESTAURANT_API ACustomerTargetPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerTargetPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* sceneComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* orderTargetPoint;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* exitFrontTargetPint;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* exitRightTargetPoint;


};
