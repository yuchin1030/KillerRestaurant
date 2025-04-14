// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RawSausage.generated.h"

UCLASS()
class KILLERRESTAURANT_API ARawSausage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARawSausage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* smComp;

	// 이동할 목표 위치 (편하게 편집 가능하게)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* A_targetLoc1;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* A_targetLoc2;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* A_targetLoc3;

	UPROPERTY()
	TArray<bool> isSausagePlaced;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class AGrilledSausage> grilledSausage_bp;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void PlaceSausage(FVector targetLoc, int32 index);
};
