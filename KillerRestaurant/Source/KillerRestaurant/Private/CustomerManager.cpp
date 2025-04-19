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

	// �մ� ��� ���� ����
	bSpawnNewCustomer = true;

	if (nextCustomer)
	{	// Check -> Exit �׽�Ʈ�� - Check �� ���������� �̰� �����ֱ�
		currentCustomer->customerState = ECustomerState::EXIT;
		
		// ���� Check(��ȭUI) �����̱� ������ IDLE �� ���
		nextCustomer->customerState = ECustomerState::IDLE;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nextCustomer is null"));
	}
}

void ACustomerManager::SetNewCustomer()
{
	// ���� �մ� ���� �� ����������
	
	//�� �մ� ����
	nextCustomer->customerState = ECustomerState::ENTRY;

	// false�� �ٲ��༭ �� �մԵ� Check -> Exit ��� �����ϰ�
	bSpawnNewCustomer = false;
	
	// ���� �մ� Destroy
	currentCustomer->Destroy();

	// �̸� ������ �մ��� ���� �մ����� �ٲ�
	currentCustomer = nextCustomer;

	// ���� �մ��� �����
	nextCustomer = nullptr;
	
}

void ACustomerManager::OrderHotdogMenuCnt()
{
	// �մ��� �ֹ��� �ֵ��� �� ����
	int32 totalMenuCnt = FMath::RandRange(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("TotalMenuCnt : %d"), totalMenuCnt);

	for (int32 i = 0; i < totalMenuCnt; ++i)
	{
		// �� �ֵ����� ����
		int32 hotdogCnt = FMath::RandRange(1, 5);

		FHotdogOrder hotdog;

		// �ߺ�üũ �Һ���
		bool bIsDuplicate = true;

		// �ߺ����� �ʴ� ������ ���� ������ �ݺ�
		while (bIsDuplicate)
		{
			hotdog.bPickle = FMath::RandBool();
			hotdog.bOnion = FMath::RandBool();
			hotdog.bKetchup = FMath::RandBool();
			hotdog.bMustard = FMath::RandBool();

			// �ߺ� üũ: OrderedHotdogs�� ������ ������ �ִ��� Ȯ��
			if (!OrderedHotdogs.Contains(hotdog))
			{
				// �ߺ����� ������ �߰��ϰ�, �ݺ� ����
				OrderedHotdogs.Add(hotdog, hotdogCnt);
				bIsDuplicate = false; // �ߺ��� �ƴϸ� while�� ����
			}
		}
	}

	for (const TPair<FHotdogOrder, int32>& Order : OrderedHotdogs)
	{
		const FHotdogOrder& Hotdog = Order.Key;
		int32 Count = Order.Value;

		// �ֵ��� ������ ������ �α׷� ���
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

