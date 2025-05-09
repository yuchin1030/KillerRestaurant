// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestListDataTable.generated.h"

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName questChapter = "0";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName questStage = "1";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText questContent;
};

class KILLERRESTAURANT_API QuestListDataTable
{
public:
	QuestListDataTable();
	~QuestListDataTable();
};
