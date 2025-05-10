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
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Dialogue;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SpeakerName;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Left;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Right;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Middle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ButtonL;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ButtonR;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ButtonM;

	TArray<float> NextIndexValues;

	UFUNCTION()
	void SetDialogueUI(FText SpeakerName, FString DialougeText, TArray<FText> Choices, TArray<float> NextIndexes);

	// 클릭 시 호출될 함수
	UFUNCTION()
	void OnButtonLeftClicked(); 

	UFUNCTION()
	void OnButtonRightClicked();

	UFUNCTION()
	void OnButtonMiddleClicked();

};
