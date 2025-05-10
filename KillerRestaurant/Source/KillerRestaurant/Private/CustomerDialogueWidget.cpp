// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerDialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "NPCManager.h"
#include "EngineUtils.h"
#include <Kismet/GameplayStatics.h>
#include <KillerRestaurantCharacter.h>

void UCustomerDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Left->SetVisibility(ESlateVisibility::Hidden);
	Button_Right->SetVisibility(ESlateVisibility::Hidden);
	Button_Middle->SetVisibility(ESlateVisibility::Hidden);
	Text_ButtonL->SetVisibility(ESlateVisibility::Hidden);
	Text_ButtonR->SetVisibility(ESlateVisibility::Hidden);
	Text_ButtonM->SetVisibility(ESlateVisibility::Hidden);

	Button_Left->OnClicked.AddDynamic(this, &UCustomerDialogueWidget::OnButtonLeftClicked);
	Button_Right->OnClicked.AddDynamic(this, &UCustomerDialogueWidget::OnButtonRightClicked);
	Button_Middle->OnClicked.AddDynamic(this, &UCustomerDialogueWidget::OnButtonMiddleClicked);

}


void UCustomerDialogueWidget::SetDialogueUI(FText SpeakerName, FString DialougeText, TArray<FText> Choices, TArray<float> NextIndexes)
{
	// 값 전달
	NextIndexValues = NextIndexes;

	Text_SpeakerName->SetText(SpeakerName);
	Text_Dialogue->SetText(FText::FromString(DialougeText));

	// 선택지 버튼이 하나일경우 가운데 버튼만 보이게
	if (Choices.Num() == 1)
	{
		Text_ButtonM->SetText(Choices[0]);
		Button_Middle->SetVisibility(ESlateVisibility::Visible);
		Text_ButtonM->SetVisibility(ESlateVisibility::Visible);

		Button_Left->SetVisibility(ESlateVisibility::Hidden);
		Button_Right->SetVisibility(ESlateVisibility::Hidden);
		Text_ButtonL->SetVisibility(ESlateVisibility::Hidden);
		Text_ButtonR->SetVisibility(ESlateVisibility::Hidden);

	}
	// 2개일 경우 좌우 버튼만 보이게
	else if (Choices.Num() == 2)
	{
		Text_ButtonL->SetText(Choices[0]);
		Text_ButtonR->SetText(Choices[1]);

		Button_Left->SetVisibility(ESlateVisibility::Visible);
		Button_Right->SetVisibility(ESlateVisibility::Visible);
		Text_ButtonL->SetVisibility(ESlateVisibility::Visible);
		Text_ButtonR->SetVisibility(ESlateVisibility::Visible);

		Button_Middle->SetVisibility(ESlateVisibility::Hidden);
		Text_ButtonM->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCustomerDialogueWidget::OnButtonLeftClicked()
{
	// 플레이어 캐릭터 가져오기
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->bShowMouseCursor = true;
		AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(PC->GetPawn());
		if (player)
		{
			player->SetNPCDialogueEntry(NextIndexValues[0]);
		}
	}
}

void UCustomerDialogueWidget::OnButtonRightClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->bShowMouseCursor = true;
		AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(PC->GetPawn());
		if (player)
		{
			player->SetNPCDialogueEntry(NextIndexValues[1]);
		}
	}
}

void UCustomerDialogueWidget::OnButtonMiddleClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->bShowMouseCursor = true;
		AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(PC->GetPawn());
		if (player)
		{
			player->SetNPCDialogueEntry(NextIndexValues[0]);
		}
	}
}

