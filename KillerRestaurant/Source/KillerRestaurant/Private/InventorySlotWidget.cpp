// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "ItemBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInventorySlotWidget::SetData(const FItemData& ItemData)
{
    // 아이템 수량 세팅
    Text_ItemAmount->SetText(FText::AsNumber(ItemData.ItemAmount));

    // 아이템 이미지 세팅
    if (Img_Item && ItemData.ItemTexture)
    {
        Img_Item->SetBrushFromTexture(ItemData.ItemTexture);
    }
}