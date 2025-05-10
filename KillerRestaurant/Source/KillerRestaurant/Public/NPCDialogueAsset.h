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

	// 이 대사가 어떤 퀘스트와 관련 있는지
	// 퀘스트 진행도에 따른 대사 식별하기 위한 고유 번호
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestID;

	// 실제 대사 내용
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Dialogue;

	// 선택지(버튼 등)로 표시될 텍스트 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Choices;

	// 선택지 따라 이동할 대사 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> NextIndexes;  

	// 현재 대사의 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DialogueIndex;  
};

UCLASS()
class KILLERRESTAURANT_API UNPCDialogueAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FNPCDialogueEntry> NPCDialogues;
};
