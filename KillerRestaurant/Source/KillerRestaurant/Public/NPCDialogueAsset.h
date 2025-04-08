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

    // 대사 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName dialogueID;

    // 대사 내용
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString dialogueText;

    // 퀘스트 진행 상태(Accepted, Completed...)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Conditions;

    // 다음 대사
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
