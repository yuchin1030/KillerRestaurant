// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomerManager.generated.h"

USTRUCT(BlueprintType)
struct FHotdogOrder
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bPickle;

	UPROPERTY(BlueprintReadWrite)
	bool bOnion;

	UPROPERTY(BlueprintReadWrite)
	bool bKetchup;

	UPROPERTY(BlueprintReadWrite)
	bool bMustard;

	UPROPERTY(BlueprintReadWrite)
	int32 hotdogCnt;

	// �񱳸� ���� == ���� �� Ű�� ������ �� �� �־����
	bool operator==(const FHotdogOrder& Other) const
	{
		return bPickle == Other.bPickle &&
			bOnion == Other.bOnion &&
			bKetchup == Other.bKetchup &&
			bMustard == Other.bMustard;
	}
};

// GetTypeHash�� ���� �� Ű�� ������ �ؽð��� �����ؾ�, ������ ã�� �浹�� ���� �� ����.
FORCEINLINE uint32 GetTypeHash(const FHotdogOrder& Order)
{
	return FCrc::MemCrc32(&Order, sizeof(FHotdogOrder));
}

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

	UPROPERTY(EditAnywhere, Category = "MySettings")
	ACustomer* currentCustomer;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	ACustomer* nextCustomer;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* A_CustomerTargetPoint;

	class ACustomerTargetPoint* customerTargetPoint;

	bool bSpawnNewCustomer;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TMap<FHotdogOrder, int32> OrderedHotdogs;

	UFUNCTION()
	void SpawnCustomer();

	UFUNCTION()
	void SetNewCustomer();

	UFUNCTION()
	void OrderHotdogMenuCnt();

	UFUNCTION()
	void Serving();
};
