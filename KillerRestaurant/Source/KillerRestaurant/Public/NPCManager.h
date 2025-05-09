// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCManager.generated.h"

UCLASS()
class KILLERRESTAURANT_API ANPCManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPCManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray<UNPCDialogueAsset*> AllDialogueDatas;

	UPROPERTY()
	class UCustomerDialogueWidget* dialogueUI;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<UUserWidget> dialogueUI_bp;

	UFUNCTION()
	FString GetNPCDialogue(const FName& SpeakerName);
};
