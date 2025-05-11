// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

UCLASS()
class KILLERRESTAURANT_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 앞으로 NPC마다 StartInteract()가 달라질 예정, 따라서 ANPCBase에 가상 함수로 정의하고, 각 자식이 override하게 만들면 더 깔끔
	// virtual 함수라면 오버라이드된 함수가 호출되어야 함
	virtual void StartInteract();

	UPROPERTY(EditAnywhere)
	FName SpeakerName;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UBoxComponent* boxColl;

	UFUNCTION()
	void OnOverlapNPCBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapNPCEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
