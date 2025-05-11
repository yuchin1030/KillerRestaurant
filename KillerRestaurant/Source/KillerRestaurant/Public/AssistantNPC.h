// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "AssistantNPC.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API AAssistantNPC : public ANPCBase
{
	GENERATED_BODY()
	
public:
	AAssistantNPC();

	virtual void StartInteract() override;
};
