// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Customer.generated.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	IDLE,
	ENTRY,
	ORDER,
	WAIT,
	CHECK,
	EXIT
};

UCLASS()
class KILLERRESTAURANT_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class ACustomerManager* cuM;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	ECustomerState customerState = ECustomerState::IDLE;

	class AAIController* AIController;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FVector exitTargetLoc;

	bool bSelectExitLocRot = false;
	bool bExitToFront;

	UFUNCTION()
	void ExitRotateAndMove(FRotator exitTargetRot, FVector _exitTargetLoc, float DeltaTime);

private:
	void Idle();
	void Entry(float _DeltaTime);
	void Order();
	void Wait(float _DeltaTime);
	void Check(float _DeltaTime);
	void Exit(float _DeltaTime);
};
