// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "MerchantNPC.generated.h"

UCLASS()
class KILLERRESTAURANT_API AMerchantNPC : public ANPCBase
{
	GENERATED_BODY()

public:
	AMerchantNPC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UFUNCTION()
	void StartInteract();


};
