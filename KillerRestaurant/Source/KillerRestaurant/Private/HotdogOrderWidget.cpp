// Fill out your copyright notice in the Description page of Project Settings.


#include "HotdogOrderWidget.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Customer.h"

void UHotdogOrderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	customer = Cast<ACustomer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomer::StaticClass()));

	if (Button_OrderAccept)
	{
		Button_OrderAccept->OnClicked.AddDynamic(this, &UHotdogOrderWidget::OnOrderAcceptClicked);
	}
}

void UHotdogOrderWidget::OnOrderAcceptClicked()
{
	// 주문 확인 버튼을 눌러야 손님 Wait 상태로 변경됨
	customer->customerState = ECustomerState::WAIT;

	RemoveFromParent(); // 창 닫기
}