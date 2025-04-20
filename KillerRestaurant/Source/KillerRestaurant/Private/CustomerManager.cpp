// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"
#include "Customer.h"
#include "CustomerTargetPoint.h"
#include <Kismet/GameplayStatics.h>
#include "KillerRestaurantCharacter.h"
#include "GameFramework/SpringArmComponent.h"

ACustomerManager::ACustomerManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerManager::BeginPlay()
{
	Super::BeginPlay();

	customerTargetPoint = Cast<ACustomerTargetPoint>(A_CustomerTargetPoint);

	currentCustomer = Cast<ACustomer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomer::StaticClass()));

	player = Cast<AKillerRestaurantCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AKillerRestaurantCharacter::StaticClass()));

}

void ACustomerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACustomerManager::OrderHotdogMenuCnt()
{
	// 손님이 주문할 핫도그 총 개수
	int32 totalMenuCnt = FMath::RandRange(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("TotalMenuCnt : %d"), totalMenuCnt);

	for (int32 i = 0; i < totalMenuCnt; ++i)
	{
		// 각 핫도그의 개수
		float hotdogCnt = FMath::RandRange(1, 5);

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
			hotdog.originalCnt = hotdogCnt;	// 원래 주문한 개수

			// 중복 체크: OrderedHotdogs에 동일한 구성이 있는지 확인
			if (!OrderedHotdogs.Contains(hotdog))
			{
				// 중복되지 않으면 추가하고, 반복 종료
				OrderedHotdogs.Add(hotdog, hotdogCnt);	// hotdogCnt 값이 감소될거임
				bIsDuplicate = false; // 중복이 아니면 while문 종료
			}
		}
	}

	for (const TPair<FHotdogOrder, float>& Order : OrderedHotdogs)
	{
		const FHotdogOrder& Hotdog = Order.Key;
		float Count = Order.Value;

		// 핫도그 구성과 개수를 로그로 출력
		UE_LOG(LogTemp, Warning, TEXT("Hotdog Order: Pickle: %s, Onion: %s, Ketchup: %s, Mustard: %s, Count: %f"),
			Hotdog.bPickle ? TEXT("Yes") : TEXT("No"),
			Hotdog.bOnion ? TEXT("Yes") : TEXT("No"),
			Hotdog.bKetchup ? TEXT("Yes") : TEXT("No"),
			Hotdog.bMustard ? TEXT("Yes") : TEXT("No"),
			Count);
	}
}

void ACustomerManager::CalculateReward(float totalSatisfaction)
{
	float percent;

	if (totalSatisfaction >= 80)
	{
		percent = 3;
	}
	else if (totalSatisfaction >= 50)
	{
		percent = 2;
	}
	else
	{
		percent = 1;
	}

	for (const auto& Order : OrderedHotdogs)
	{
		// 각 핫도그 메뉴 구성
		const FHotdogOrder& Hotdog = Order.Key;

		// 각 핫도그 남은 개수
		float remainCnt = Order.Value;

		// 각 핫도그 당 기본 가격
		float eachTotalPrice = Hotdog.CalculatePrice();

		// 서빙한 개수만큼 계산
		float servedCnt = Hotdog.originalCnt - remainCnt;

		allTotalPrice += eachTotalPrice * servedCnt * percent;

		UE_LOG(LogTemp, Warning, TEXT("eachTotalPrice : %f servedCnt : %f percent : %f"), eachTotalPrice, servedCnt, percent);
	}


	if (player)
	{
		player->playerGold += allTotalPrice;
		UE_LOG(LogTemp, Warning, TEXT("allTotalPrice : %f player->playerGold : %f"), allTotalPrice, player->playerGold);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player is null"));
	}
}

void ACustomerManager::SetPlayerCameraView(bool bWaiting)
{
	player->GetCameraBoom()->bUsePawnControlRotation = !bWaiting;

	// 주문 받았으면 요리 시점으로 변경 - Customer : Wait 상태
	if (bWaiting)
	{
		player->GetCameraBoom()->SetRelativeLocation(FVector(48, 0, 259));
		player->GetCameraBoom()->SetRelativeRotation(FRotator(-37.070497, 0, 0));
	}
	// 끝났으면 주문 시점으로 변경 - Customer : Check 상태
	else
	{
		player->GetCameraBoom()->SetRelativeLocation(FVector(0));
		player->GetCameraBoom()->SetRelativeRotation(FRotator(0));
	}
	
}

void ACustomerManager::SpawnCustomer()
{
	// 주문 목록 배열 비워주기
	OrderedHotdogs.Empty();
	allTotalPrice = 0;

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
