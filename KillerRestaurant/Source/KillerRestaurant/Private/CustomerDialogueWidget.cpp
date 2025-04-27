// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerDialogueWidget.h"
#include "Components/TextBlock.h"

void UCustomerDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}


void UCustomerDialogueWidget::SetDialogueText(FString text)
{
	Text_Dialogue->SetText(FText::FromString(text));
}
