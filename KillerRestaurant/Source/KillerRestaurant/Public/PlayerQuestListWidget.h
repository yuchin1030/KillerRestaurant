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
	virtual void NativeConstruct() override;

	UPROPERTY()
	class UMyGameInstance* gi;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_QuestChapter;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_QuestStage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_QuestContent;
	
	UFUNCTION()
	void UpdateQuestUI(FName Chapter, FName Stage);

	UFUNCTION(BlueprintImplementableEvent)
	void CompleteStartQuest();



};
