// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "ItemBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventorySlotWidget::SetData(const FItemData& ItemData)
{
    CurrentItemData = ItemData;

    // 아이템 수량 세팅
    if (Text_ItemAmount)
    {
        Text_ItemAmount->SetText(FText::AsNumber(ItemData.ItemAmount));
    }

    // 아이템 이미지 세팅
    if (Img_Item && ItemData.ItemTexture)
    {
        Img_Item->SetBrushFromTexture(ItemData.ItemTexture);
    }
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // 마우스 좌클릭일 때만 드래그 시작
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        return EventReply.NativeReply;
    }
    return FReply::Handled();
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    // 드래그 중에 보여줄 위젯 생성
    UInventorySlotWidget* DragVisual = CreateWidget<UInventorySlotWidget>(GetWorld(), StaticClass());
    DragVisual->SetData(CurrentItemData);

    UDragDropOperation* DragOp = NewObject<UDragDropOperation>();

    if (DragOp)
    {
        DragOp->DefaultDragVisual = this; // 또는 복제본
        DragOp->Pivot = EDragPivot::MouseDown;
        DragOp->Payload = this; // 드래그 중인 슬롯 위젯 참조

        OutOperation = DragOp;

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No DragOp"));
    }

    // 드래그 중이므로 기존 위치에서 보이지 않게 처리
    SetVisibility(ESlateVisibility::Hidden);
}


bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->Payload)
    {
        // Payload에서 드래그한 아이템 위젯 가져오기
        UInventorySlotWidget* FromSlot = Cast<UInventorySlotWidget>(InOperation->Payload);
        if (FromSlot)
        {
            // 예: 아이템 교환 로직
            FItemData Temp = CurrentItemData;
            SetData(FromSlot->CurrentItemData);
            FromSlot->SetData(Temp);

            // 게임 로직 반영 필요 시 따로 아이템 교환 함수 호출
            return true;
        }
    }
    return false;
}