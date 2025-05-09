// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuestListWidget.h"
#include "MyGameInstance.h"
#include "QuestListDataTable.h" // FQuestData 정의된 곳
#include "Components/TextBlock.h"

void UPlayerQuestListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
}

// 퀘스트창 갱신
void UPlayerQuestListWidget::UpdateQuestUI(FName Chapter, FName Stage)
{
	if (!gi)
	{
		UE_LOG(LogTemp, Warning, TEXT("No gi"));
		return;

	}

	if (!gi->DT_QuestList)
	{
		UE_LOG(LogTemp, Warning, TEXT("No DT_QuestList"));
		return;
	}

	// TEXT("Lookup Quest Row") : 디버그 메시지용 컨텍스트 문자열
	// 문제가 생겼을 때 로그 메시지에 어디서 호출했는지 알려줌
	const FQuestData* QuestRow = gi->DT_QuestList->FindRow<FQuestData>(gi->GetRowKey(Chapter, Stage), TEXT("Lookup Quest Row"));

	// 해당 row가 있다면
	if (QuestRow)
	{
		Text_QuestChapter->SetText(FText::FromName(QuestRow->questChapter));
		Text_QuestStage->SetText(FText::FromName(QuestRow->questStage));
		Text_QuestContent->SetText(QuestRow->questContent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest row not found for %s"), *gi->GetRowKey(Chapter, Stage).ToString());
	}
}
