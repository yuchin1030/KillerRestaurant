// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "ItemBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventorySlotWidget::SetData(const FItemData& ItemData)
{
    CurrentItemData = ItemData;

    if (ItemData.ItemName == NAME_None || ItemData.ItemAmount <= 0)
    {
        if (Text_ItemAmount)
        {
            Text_ItemAmount->SetText(FText::FromString(TEXT("")));
        }

        // 아이템이 비어있다면 디폴트 이미지 사용
        if (Img_Item && EmptyTexture)
        {
            Img_Item->SetBrushFromTexture(EmptyTexture);
        }
    }
    else
    {
        // 아이템 수량 세팅
        if (Text_ItemAmount)
        {
            Text_ItemAmount->SetText(FText::AsNumber(CurrentItemData.ItemAmount));
        }

        // 아이템 이미지 세팅
        if (Img_Item && CurrentItemData.ItemTexture)
        {
            Img_Item->SetBrushFromTexture(CurrentItemData.ItemTexture);
            UE_LOG(LogTemp, Warning, TEXT("ItemTexture: %s"), *GetNameSafe(CurrentItemData.ItemTexture));
        }
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
    BackupItemData = CurrentItemData; // 백업 저장

    // 드래그 중에 보여줄 위젯 생성
    UInventorySlotWidget* DragVisual = CreateWidget<UInventorySlotWidget>(GetWorld(), StaticClass());
    //UE_LOG(LogTemp, Warning, TEXT("ItemName: %s, Amount: %d"), *CurrentItemData.ItemName.ToString(), CurrentItemData.ItemAmount);
    DragVisual->SetData(CurrentItemData);
    DragVisual->AddToViewport();

    UDragDropOperation* DragOp = NewObject<UDragDropOperation>();

    if (DragOp)
    {
        DragOp->DefaultDragVisual = DragVisual; // 또는 복제본
        DragOp->Pivot = EDragPivot::MouseDown;
        DragOp->Payload = this; // 드래그 중인 슬롯 위젯 참조

        OutOperation = DragOp;

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No DragOp"));
    }

    // 드래그 중이므로 기존 위치 빈슬롯으로
    FItemData EmptyData;
    EmptyData.ItemName = NAME_None; 
    EmptyData.ItemAmount = 0;
    SetData(EmptyData);
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
            SetData(FromSlot->BackupItemData);
            FromSlot->SetData(Temp);

            // 게임 로직 반영 필요 시 따로 아이템 교환 함수 호출
            return true;
        }
    }
    return false;
}