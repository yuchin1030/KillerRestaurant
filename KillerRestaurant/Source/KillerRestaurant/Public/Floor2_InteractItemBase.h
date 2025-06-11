// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor2_InteractItemBase.generated.h"

UCLASS()
class KILLERRESTAURANT_API AFloor2_InteractItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloor2_InteractItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void ChangeCameraView();
};
