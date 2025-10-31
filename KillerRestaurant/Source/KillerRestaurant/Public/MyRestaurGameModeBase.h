// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyRestaurGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AMyRestaurGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AMyRestaurGameModeBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class AKillerRestaurantCharacter* player;

	UPROPERTY(EditAnywhere)
	class ACustomerManager* cuM;

	UPROPERTY()
	int32 gameHour = 17;	// 12시 시작

	UPROPERTY()
	int32 gameMinute = 50;	// 00분 시작

	UPROPERTY()
	float timeElapsed = 0;  // 실제 경과된 시간

	// 7분 동안 360분이 흐르려면 → 게임 시간 1분 = 실제 시간 약 1.17초
	// 8분 동안 360분이 흐르려면 → 게임 시간 1분 = 실제 시간 약 1.33초
	UPROPERTY()
	float timeSpeed = 1.33f;

	bool bClosingTime = false;
};
