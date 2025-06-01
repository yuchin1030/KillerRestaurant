// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCManager.h"
#include "NPCDialogueAsset.h"
#include "CustomerDialogueWidget.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"

ANPCManager::ANPCManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANPCManager::BeginPlay()
{
	Super::BeginPlay();
	
	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.PackagePaths.Add("/Game/Yuchin/DataAssets");
	Filter.ClassPaths.Add(FTopLevelAssetPath(TEXT("/Script/KillerRestaurant.NPCDialogueAsset")));

	// 1.  (Build.cs에 AssetRegistry 모듈 추가 필수)
	// 2. "AssetRegistryModule.h", "Engine/AssetManager.h" 헤더 추가해야함 
	// Unreal이 제대로 헤더 경로를 못 잡을 때가 있음 --> 이럴 땐 "AssetRegistryModule.h" 경로를 절대 경로 스타일인 "AssetRegistry/AssetRegistryModule.h"로 바꿔줘야함
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssets(Filter, AssetList);

	for (const FAssetData& Asset : AssetList)
	{
		UNPCDialogueAsset* DialogueAsset = Cast<UNPCDialogueAsset>(Asset.GetAsset());
		if (DialogueAsset)
		{
			AllDialogueDatas.Add(DialogueAsset);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NPCDialogueAsset is null"));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("NPCDialogueAsset: Loaded %d Dialogue Assets"), AllDialogueDatas.Num());

	if (dialogueUI_bp)
	{
		dialogueUI = CreateWidget<UCustomerDialogueWidget>(GetWorld(), dialogueUI_bp);

		if (dialogueUI)
		{
			dialogueUI->AddToViewport();
			dialogueUI->SetVisibility(ESlateVisibility::Hidden); // 초기에 화면에 안 보이게 설정
		}
	}
}

void ANPCManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FNPCDialogueEntry ANPCManager::GetDialogueEntry(const FName& SpeakerName, FName CurrentQuestID, float CurrentDialogueIndex)
{
	for (UNPCDialogueAsset* Data : AllDialogueDatas)
	{
		if (Data)
		{
			for (const FNPCDialogueEntry& Entry : Data->NPCDialogues)
			{
				if (Entry.Speaker.ToString() == SpeakerName.ToString() &&
					Entry.QuestID == CurrentQuestID &&
					Entry.DialogueIndex == CurrentDialogueIndex)
				{
					return Entry;
				}
			}
		}
	}

	return FNPCDialogueEntry();
}

void ANPCManager::ShowDialogueUI(FNPCDialogueEntry _Entry)
{
	dialogueUI->SetDialogueUI(_Entry.Speaker, _Entry.Dialogue, _Entry.Choices, _Entry.NextIndexes);
	dialogueUI->SetVisibility(ESlateVisibility::Visible);

	UE_LOG(LogTemp, Warning, TEXT("_Entry.Speaker: %s : %s"), *_Entry.Speaker.ToString(), *_Entry.Dialogue);

}

