// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor2_ColorItemBase.generated.h"

UCLASS()
class KILLERRESTAURANT_API AFloor2_ColorItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloor2_ColorItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* sceneComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* smComp;

	int32 cnt = 0;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<FString> materialPaths;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<UMaterialInterface*> loadedMaterials;

	UFUNCTION()
	void ChangeColor();
};
