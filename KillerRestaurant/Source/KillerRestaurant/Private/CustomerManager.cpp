// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"
#include "Customer.h"
#include "CustomerTargetPoint.h"
#include <Kismet/GameplayStatics.h>

ACustomerManager::ACustomerManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerManager::BeginPlay()
{
	Super::BeginPlay();

	customerTargetPoint = Cast<ACustomerTargetPoint>(A_CustomerTargetPoint);

	currentCustomer = Cast<ACustomer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomer::StaticClass()));
}

void ACustomerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomerManager::SpawnCustomer()
{
	OrderedHotdogs.Empty();

	FActorSpawnParameters params;
	nextCustomer = GetWorld()->SpawnActor<ACustomer>(customer_bp, customerStartLoc, FRotator::ZeroRotator, params);

	// 손님 계속 스폰 방지
	bSpawnNewCustomer = true;

	if (nextCustomer)
	{	// Check -> Exit 테스트용 - Check 다 구현했으면 이거 지워주기
		currentCustomer->customerState = ECustomerState::EXIT;
		
		// 아직 Check(대화UI) 상태이기 때문에 IDLE 로 대기
		nextCustomer->customerState = ECustomerState::IDLE;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nextCustomer is null"));
	}
}

void ACustomerManager::SetNewCustomer()
{
	// 기존 손님 거의 다 퇴장했을때
	
	//새 손님 입장
	nextCustomer->customerState = ECustomerState::ENTRY;

	// false로 바꿔줘서 새 손님도 Check -> Exit 기능 가능하게
	bSpawnNewCustomer = false;
	
	// 기존 손님 Destroy
	currentCustomer->Destroy();

	// 미리 스폰한 손님이 현재 손님으로 바뀜
	currentCustomer = nextCustomer;

	// 다음 손님은 비워둠
	nextCustomer = nullptr;
	
}

void ACustomerManager::OrderHotdogMenuCnt()
{
	// 손님이 주문할 핫도그 총 개수
	int32 totalMenuCnt = FMath::RandRange(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("TotalMenuCnt : %d"), totalMenuCnt);

	for (int32 i = 0; i < totalMenuCnt; ++i)
	{
		// 각 핫도그의 개수
		int32 hotdogCnt = FMath::RandRange(1, 5);

		FHotdogOrder hotdog;

		// 중복체크 불변수
		bool bIsDuplicate = true;

		// 중복되지 않는 구성이 나올 때까지 반복
		while (bIsDuplicate)
		{
			hotdog.bPickle = FMath::RandBool();
			hotdog.bOnion = FMath::RandBool();
			hotdog.bKetchup = FMath::RandBool();
			hotdog.bMustard = FMath::RandBool();

			// 중복 체크: OrderedHotdogs에 동일한 구성이 있는지 확인
			if (!OrderedHotdogs.Contains(hotdog))
			{
				// 중복되지 않으면 추가하고, 반복 종료
				OrderedHotdogs.Add(hotdog, hotdogCnt);
				bIsDuplicate = false; // 중복이 아니면 while문 종료
			}
		}
	}

	for (const TPair<FHotdogOrder, int32>& Order : OrderedHotdogs)
	{
		const FHotdogOrder& Hotdog = Order.Key;
		int32 Count = Order.Value;

		// 핫도그 구성과 개수를 로그로 출력
		UE_LOG(LogTemp, Warning, TEXT("Hotdog Order: Pickle: %s, Onion: %s, Ketchup: %s, Mustard: %s, Count: %d"),
			Hotdog.bPickle ? TEXT("Yes") : TEXT("No"),
			Hotdog.bOnion ? TEXT("Yes") : TEXT("No"),
			Hotdog.bKetchup ? TEXT("Yes") : TEXT("No"),
			Hotdog.bMustard ? TEXT("Yes") : TEXT("No"),
			Count);
	}
}

void ACustomerManager::Serving()
{
	
}

