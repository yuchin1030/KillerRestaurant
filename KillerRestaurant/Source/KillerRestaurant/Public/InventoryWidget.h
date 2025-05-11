// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    // 슬롯을 넣을 유니폼 그리드 패널 (디자이너에서 바인딩)
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* InventoryGridPanel;

    // 슬롯 위젯 블루프린트 클래스 설정용
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    TSubclassOf<UUserWidget> SlotWidget_wbp;

    UPROPERTY()
    TArray<UInventorySlotWidget*> inventorySlots;

    // 슬롯 총 개수
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    int32 slotsNum = 25;

    // 열
    UPROPERTY(EditDefaultsOnly, Category = "MySettings")
    int32 colsNum = 5;

    UFUNCTION()
    void UpdateInventory(const TArray<FItemData>& InventoryData);
};
