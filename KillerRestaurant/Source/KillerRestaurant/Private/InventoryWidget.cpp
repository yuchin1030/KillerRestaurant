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
    // 아직 표시할 인벤토리 데이터가 남아 있는지 확인, 슬롯 배열 크기보다 초과되지 않는지 확인
    // 두 배열 중 작은 쪽의 길이만큼만 루프
    for (int32 i = 0; i < InventoryData.Num() && i < inventorySlots.Num(); i++)
    {
        inventorySlots[i]->SetData(InventoryData[i]);
    }
}
