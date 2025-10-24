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

	// 플레이어 캐릭터 가져오기
	player = Cast<AKillerRestaurantCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}


void UCustomerDialogueWidget::SetDialogueUI(FText SpeakerName, FString DialougeText, TArray<FText> Choices, TArray<float> NextIndexes)
{
	// 값 전달
	NextIndexValues = NextIndexes;

	Text_SpeakerName->SetText(SpeakerName);
	Text_Dialogue->SetText(FText::FromString(DialougeText));

	// 선택지 버튼이 1개일 경우 가운데 버튼만 보이게
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
	// 선택지 버튼이 2개일 경우 좌우 버튼만 보이게
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
	// 선택지 버튼이 아예 없을 경우 모든 버튼 Hidden
	else
	{
		Button_Left->SetVisibility(ESlateVisibility::Hidden);
		Button_Right->SetVisibility(ESlateVisibility::Hidden);
		Text_ButtonL->SetVisibility(ESlateVisibility::Hidden);
		Text_ButtonR->SetVisibility(ESlateVisibility::Hidden);

		Button_Middle->SetVisibility(ESlateVisibility::Hidden);
		Text_ButtonM->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

// SetDialogueUI() 이후에 ButtonClicked가 발생하기 때문에
//  SetDialogueUI()에서 NextIndexValues 값을 전달 받아서 다음 대사 존재 유무 확인 가능
void UCustomerDialogueWidget::OnButtonLeftClicked()
{
	// 다음 대사가 있으면
	if (NextIndexValues.Num() > 0)
	{
		// 다음 대사 불러오기
		// 배열은 어차피 값 최대 2개 (왼쪽 버튼 값 : 배열 0번째 값)
		RequestNextDialogue(NextIndexValues[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCustomerDialogueWidget : No Next Index - Dialogue Ends"));
	}

}

void UCustomerDialogueWidget::OnButtonRightClicked()
{
	if (NextIndexValues.Num() > 0)
	{
		// 다음 대사 불러오기
		// 배열은 어차피 값 최대 2개 (오른쪽 버튼 값 : 배열 1번째 값)
		RequestNextDialogue(NextIndexValues[1]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCustomerDialogueWidget : No Next Index - Dialogue Ends"));
	}
}

void UCustomerDialogueWidget::OnButtonMiddleClicked()
{
	// 다음 대사 있으면
	if (NextIndexValues.Num() > 0)
	{
		// 다음 대사 불러오기
		// 배열은 어차피 값 최대 2개 (가운데 버튼 값 : 배열 0번째 값)
		RequestNextDialogue(NextIndexValues[0]);
	}
	else
	{
		// 가운데 버튼 눌렀을때 현재 다음 대사 없으면 숨김처리 (Choices 버튼 1개(:OK), NextIndexValues 값 Empty
		this->SetVisibility(ESlateVisibility::Hidden);

		// NPC와 상호작용 끝났을 경우(UI 대화창 닫혔을 경우) 플레이어 시선 및 움직임 활성화
		player->SetInputBlocked(false);
		player->ButtonClickedTrigger(0.2);

		UE_LOG(LogTemp, Warning, TEXT("UCustomerDialogueWidget : No Next Index - Dialogue Ends"));
		
	}

}

void UCustomerDialogueWidget::RequestNextDialogue(float NextDialogueIndex)
{
	if (player)
	{
		player->SetNPCDialogueEntry(NextDialogueIndex);	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCustomerDialogueWidget : NO player"));

	}
}

