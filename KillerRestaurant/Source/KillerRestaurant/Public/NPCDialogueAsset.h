// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCDialogueAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FDialogueLine
{
    GENERATED_BODY()

    // ��� ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName dialogueID;

    // ��� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString dialogueText;

    // ����Ʈ ���� ����(Accepted, Completed...)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Conditions;

    // ���� ���
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> NextDialogueIDs;
};

UCLASS()
class KILLERRESTAURANT_API UNPCDialogueAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDialogueLine> dialogueLines;
};
