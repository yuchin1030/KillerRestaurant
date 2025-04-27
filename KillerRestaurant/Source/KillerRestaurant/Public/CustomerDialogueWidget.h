// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomerDialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API UCustomerDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Dialogue;

	UFUNCTION()
	void SetDialogueText(FString text);

};
