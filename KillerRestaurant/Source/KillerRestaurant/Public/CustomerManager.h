// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomerManager.generated.h"

UCLASS()
class KILLERRESTAURANT_API ACustomerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<ACustomer> customer_bp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FVector customerStartLoc = FVector(724, -1157, 94);

	UFUNCTION()
	void SpawnCustomer();
};
