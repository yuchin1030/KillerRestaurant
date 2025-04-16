// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PicklesBox.generated.h"

UCLASS()
class KILLERRESTAURANT_API APicklesBox : public AActor
{
	GENERATED_BODY()
	
public:	
	APicklesBox();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* smComp;
};
