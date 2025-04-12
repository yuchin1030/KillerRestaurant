// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dough.generated.h"

UCLASS()
class KILLERRESTAURANT_API ADough : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADough();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* smComp;

	// �̵��� ��ǥ ��ġ (���ϰ� ���� �����ϰ�)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	AActor* TargetLocationActor;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
