// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotdogOrderWidget.generated.h"

/**
 * 
 */
UCLASS()
class KILLERRESTAURANT_API UHotdogOrderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 확인 버튼 바인딩
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_OrderAccept;

	class ACustomer* customer;

protected:
	virtual void NativeOnInitialized() override;

private:
	// 확인 버튼 클릭 시 호출할 함수
	UFUNCTION()
	void OnOrderAcceptClicked();
};
