// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCDialogueAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FNPCDialogueEntry
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Dialogue;

	// 선택지(버튼 등)로 표시될 텍스트 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Choices;

	// 선택지 따라 이동할 대사 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NextIndexes;  
};

UCLASS()
class KILLERRESTAURANT_API UNPCDialogueAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FNPCDialogueEntry> Dialogues;
};
