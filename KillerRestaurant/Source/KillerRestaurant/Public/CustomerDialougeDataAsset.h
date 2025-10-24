// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CustomerDialougeDataAsset.generated.h"

UENUM(BlueprintType)
enum class ESatisfactionGrade : uint8
{
    LOW,
    MID,
    HIGH
};

USTRUCT(BlueprintType)
struct FClueDialogueEntry
{
    GENERATED_BODY()

    // 이 대사가 어떤 퀘스트와 관련 있는지
    // 퀘스트 진행도에 따른 대사 식별하기 위한 고유 번호
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName QuestID;

    // 만족도 등급
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ESatisfactionGrade SatisGrade;

    // 실제 대사 내용
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Dialogue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FText> Choices;
};

UCLASS()
class KILLERRESTAURANT_API UCustomerDialougeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    // 퀘스트 단서 대사 or 일상 대사 여부
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bIsQuestClueDialogue = false;

    // 만족도에 따른 일상 대사 묶음
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FString> dailyHighSatisDialogs;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FString> dailyMidSatisDialogs;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FString> dailyLowSatisDialogs;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FClueDialogueEntry> questClueDialogues;
	
};
