// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor3ObstacleBase.generated.h"

USTRUCT(BlueprintType)
struct FObstacleInfo
{
    GENERATED_BODY()

public:
    // ====== 공통 설정 ======
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
    float damage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
    float ActivationDelay = 0.0f;

    // 불 장애물 전용
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
    bool bCanInteract = false;
};

UCLASS()
class KILLERRESTAURANT_API AFloor3ObstacleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloor3ObstacleBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
    FObstacleInfo ObstacleInfo;

    class AKillerRestaurantCharacter* player;

    // 오버랩 시작 시 데미지 처리 함수
    UFUNCTION()
    virtual void OnObstacleOverlapDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 오버랩 시작 시 상호작용 처리 함수
    UFUNCTION()
    virtual void OnObstacleOverlapInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 오버랩 종료 후 상호작용 처리 함수
    UFUNCTION()
    void OnObstacleOverlapInteractEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
