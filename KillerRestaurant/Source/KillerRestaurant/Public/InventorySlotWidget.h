// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemBase.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ItemAmount;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY()
	FItemData CurrentItemData;

	FItemData BackupItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	UTexture2D* EmptyTexture;

	UFUNCTION()
	void SetData(const FItemData& ItemData);

	// 드래그 시작
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
