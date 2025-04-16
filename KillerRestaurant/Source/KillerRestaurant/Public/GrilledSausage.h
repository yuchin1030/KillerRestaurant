// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrilledSausage.generated.h"

UCLASS()
class KILLERRESTAURANT_API AGrilledSausage : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrilledSausage();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* smComp;

	//UPROPERTY()
	//TArray<bool> isGrilled;

	//UPROPERTY()
	bool isGrilled;
	bool isBurned;

	UPROPERTY()
	float grillTime = 7.f;

	UFUNCTION()
	void Grill();
};
