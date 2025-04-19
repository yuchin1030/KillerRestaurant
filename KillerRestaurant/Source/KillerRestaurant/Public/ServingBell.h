// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServingBell.generated.h"

UCLASS()
class KILLERRESTAURANT_API AServingBell : public AActor
{
	GENERATED_BODY()
	
public:	
	AServingBell();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* sceneComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* sm_FirstBell;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* sm_SecondBell;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* sm_ThirdBell;
};
