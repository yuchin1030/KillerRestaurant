// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MustardBox.generated.h"

UCLASS()
class KILLERRESTAURANT_API AMustardBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AMustardBox();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* smComp;
};
