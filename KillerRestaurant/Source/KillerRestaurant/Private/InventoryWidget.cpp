// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "ItemBase.h"

void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!SlotWidget_wbp || !InventoryGridPanel)
    {
        UE_LOG(LogTemp, Warning, TEXT("SlotWidgetClass or InventoryGridPanel is not set!"));
        return;
    }

    for (int32 i = 0; i < slotsNum; ++i)
    {
        UInventorySlotWidget* newSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotWidget_wbp);

        if (newSlot)
        {
            // 행
            int32 row = i / colsNum;
            // 열
            int32 col = i % colsNum;

            InventoryGridPanel->AddChildToUniformGrid(newSlot, row, col);
           
            // 나중에 접근할 수 있게 저장
            inventorySlots.Add(newSlot);
        }
    }
}

void UInventoryWidget::UpdateInventory(const TArray<FItemData>& InventoryData)
{
    // 실제 인벤토리 데이터 채워넣기
    for (int32 i = 0; i < InventoryData.Num() && i < inventorySlots.Num(); ++i)
    {
        inventorySlots[i]->SetData(InventoryData[i]);
    }
}
