// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerQuestListWidget.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API UPlayerQuestListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CompleteStartQuest();
};
