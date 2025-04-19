// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookManager.generated.h"

USTRUCT(BlueprintType)
struct FHotdogTopping
{
	GENERATED_BODY()

	UPROPERTY()
	bool bPickles;

	UPROPERTY()
	bool bOnions;

	UPROPERTY()
	bool bKetchup;

	UPROPERTY()
	bool bMustard;
};


UCLASS()
class KILLERRESTAURANT_API ACookManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACookManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<class AStretchedDough*> spawnedBreads;

	UPROPERTY(EditAnywhere)
	TArray<class AGrilledSausage*> spawnedSausages;

	// 이동할 목표 위치 (편하게 편집 가능하게)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* bread_targetLoc1;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* bread_targetLoc2;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* bread_targetLoc3;

	// 이동할 목표 위치 (편하게 편집 가능하게)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* sausage_targetLoc1;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* sausage_targetLoc2;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* sausage_targetLoc3;

	UPROPERTY()
	TArray<bool> isDoughPlaced;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class AStretchedDough> stretchDough_bp;

	UPROPERTY()
	TArray<bool> isSausagePlaced;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class AGrilledSausage> grilledSausage_bp;

	UPROPERTY()
	int32 suasageCurIndex;

	UPROPERTY()
	TArray<FHotdogTopping> completedHotdogs;

	UFUNCTION()
	void SpawnBread();

	UFUNCTION()
	void PlaceBread(FVector b_targetLoc, int32 index);

	UFUNCTION()
	void SpawnSausage();

	UFUNCTION()
	void PlaceSausage(FVector s_targetLoc, int32 index);

	void InsertGrilledSausageToBread(AGrilledSausage* grilledSausage, int32 curSausageIndex);

	UFUNCTION()
	void PlacePickles();

	UFUNCTION()
	void PlaceOnions();

	UFUNCTION()
	void PlaceKetchup();

	UFUNCTION()
	void PlaceMustard();

	UFUNCTION()
	void FinishMaking(int32 bellNum_);
};
