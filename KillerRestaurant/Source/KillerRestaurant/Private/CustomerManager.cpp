// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"
#include "Customer.h"
#include "CustomerTargetPoint.h"
#include <Kismet/GameplayStatics.h>
#include "KillerRestaurantCharacter.h"
#include "Camera/CameraComponent.h"
#include "CustomerDialougeDataAsset.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"
#include "CustomerDialogueWidget.h"

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

	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.PackagePaths.Add("/Game/Yuchin/DataAssets");
	Filter.ClassPaths.Add(FTopLevelAssetPath(TEXT("/Script/KillerRestaurant.CustomerDialougeDataAsset")));

	// 1.  (Build.cs에 AssetRegistry 모듈 추가 필수)
	// 2. "AssetRegistryModule.h", "Engine/AssetManager.h" 헤더 추가해야함 
	// Unreal이 제대로 헤더 경로를 못 잡을 때가 있음 --> 이럴 땐 "AssetRegistryModule.h" 경로를 절대 경로 스타일인 "AssetRegistry/AssetRegistryModule.h"로 바꿔줘야함
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssets(Filter, AssetList);

	for (const FAssetData& Asset : AssetList)
	{
		UCustomerDialougeDataAsset* DialogueAsset = Cast<UCustomerDialougeDataAsset>(Asset.GetAsset());
		if (DialogueAsset)
		{
			AllDialogueDatas.Add(DialogueAsset);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CustomerDialougeDataAsset is null"));
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("CustomerDialougeDataAsset: Loaded %d Dialogue Assets"), AllDialogueDatas.Num());

	if (dialogueUI_bp)
	{
		dialogueUI = CreateWidget<UCustomerDialogueWidget>(GetWorld(), dialogueUI_bp);

		if (dialogueUI)
		{
			dialogueUI->AddToViewport();
			dialogueUI->SetVisibility(ESlateVisibility::Hidden); // 초기에 화면에 안 보이게 설정
		}
	}

}

void ACustomerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCameraTransitioning)
	{
		UCameraComponent* camera = player->GetFollowCamera();

		// 위치 및 회전을 부드럽게 변화시키기 위한 보간 함수
		// VInterpTo(현재위치, 목표위치, DeltaTime, 속도) - 현재위치에서 목표위치까지 부드럽게 이동
		// RInterpTo(현재회전값, 목표회전값, DeltaTime, 속도) - 현재회전값에서 목표회전값까지 부드럽게 회전
		FVector newLoc = FMath::VInterpTo(camera->GetRelativeLocation(), cameraTargetLoc, DeltaTime, cameraLerpSpeed);
		FRotator newRot = FMath::RInterpTo(camera->GetRelativeRotation(), cameraTargetRot, DeltaTime, cameraLerpSpeed);

		camera->SetRelativeLocation(newLoc);
		camera->SetRelativeRotation(newRot);

		// 완료 체크 (목표위치와 목표 회전에 거의 도달했으면 멈춤)
		if (FVector::Dist(newLoc, cameraTargetLoc) < 1.f && FMath::Abs((newRot - cameraTargetRot).Yaw) < 1.f)
		{
			bCameraTransitioning = false;
		}
	}
}


void ACustomerManager::OrderHotdogMenuCnt()
{
	bOrdered = true;

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

void ACustomerManager::SetPlayerCameraView(bool bWaiting)
{
	bCameraTransitioning = true;

	//player->GetCameraBoom()->bUsePawnControlRotation = !bWaiting;

	if (bWaiting)
	{
		//player->GetCameraBoom()->TargetArmLength = 400;
		cameraTargetLoc = FVector(10, 0, 356);
		cameraTargetRot = FRotator(-55, 0, 0);
	}
	else
	{
		cameraTargetLoc = FVector(320, 0, 144);
		cameraTargetRot = FRotator(0);
	}
	//// 주문 받았으면 요리 시점으로 변경 - Customer : Wait 상태
	//if (bWaiting)
	//{
	//	player->GetCameraBoom()->SetRelativeLocation(FVector(219, 0, 222));
	//	player->GetCameraBoom()->SetRelativeRotation(FRotator(-47, 0, 0));
	//}
	//// 끝났으면 주문 시점으로 변경 - Customer : Check 상태
	//else
	//{
	//	player->GetCameraBoom()->SetRelativeLocation(FVector(500, 0, 0));
	//	player->GetCameraBoom()->SetRelativeRotation(FRotator(0));
	//}
	
}

void ACustomerManager::SetClosing()
{
	if (currentCustomer->customerState == ECustomerState::IDLE)
	{
		if (currentCustomer)
			currentCustomer->Destroy();

		bCanPlaying = false;
	}
	else if (currentCustomer->customerState == ECustomerState::ENTRY || currentCustomer->customerState == ECustomerState::ORDER)
	{
		currentCustomer->customerState = ECustomerState::EXIT;
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

	// false로 바꿔줘서 새 손님도 Check -> Exit 기능 가능하게 + 주문 가능하게
	bSpawnNewCustomer = false;
	bOrdered = false;

	// 기존 손님 Destroy
	currentCustomer->Destroy();

	// 미리 스폰한 손님이 현재 손님으로 바뀜
	currentCustomer = nextCustomer;

	// 다음 손님은 비워둠
	nextCustomer = nullptr;

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

FClueDialogueEntry ACustomerManager::GetCustomerDialogue(float satisfaction)
{
	FClueDialogueEntry Result;

	// 만족도 등급 설정
	ESatisfactionGrade grade;

	if (satisfaction >= 80)
		grade = ESatisfactionGrade::HIGH;
	else if (satisfaction >= 50)
		grade = ESatisfactionGrade::MID;
	else
		grade = ESatisfactionGrade::LOW;

	// 관련 대사 데이터 찾아오기
	for (UCustomerDialougeDataAsset* data : AllDialogueDatas)
	{
		// 퀘스트대사, 일상대사
		// 퀘스트1상태이면 퀘스트1대사, 2상태이면 2대사 ...
		// 평상시에 일상 대사
		// 확률을 어떻게 할 것인가 - 50
		if (!data)
		{
			UE_LOG(LogTemp, Warning, TEXT("data is null"));
			continue;
		}

		// 퀘스트 대사 줄지 일상 대사 줄지 정함(확률:50 - 나중에 확률 바꿀거면 RandomBoolWithWeight 쓰기
		bool bGiveClue = FMath::RandBool();

		UE_LOG(LogTemp, Warning, TEXT("bGiveClue : %d"), bGiveClue);

		TArray<FString> Candidates;
		TArray<FText> Choices;

		// 퀘스트 대사 주는 경우
		if (bGiveClue)
		{
			for (const FClueDialogueEntry& Entry : data->questClueDialogues)
			{
				// 이 대사의 퀘스트 번호가 플레이어 현재 퀘스트 진행도 번호와 동일하고, 만족도 등급이 현재 손님 만족도 등급과 동일하면
				if (Entry.QuestID == player->playercurrentQuestID && Entry.SatisGrade == grade)
				{
					// 임의 배열에 Add
					Candidates.Add(Entry.Dialogue);
					Result.Choices = Entry.Choices;
				}
			}

			// 현재 퀘스트 진행도와 손님 만족도를 만족하는 대사들이 담겨있는 임의 대사 배열에서 랜덤으로 하나 고르기(ex.높 - 높 대사들 10개 중 하나 출력)
			if (Candidates.Num() > 0)
			{
				int32 RandIdx = FMath::RandRange(0, Candidates.Num() - 1);
				Result.Dialogue = Candidates[RandIdx];

				return Result;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Candidates is null"));
			}


			return Result;
		}
		// 일상 대사 주는 경우
		else
		{
			const TArray<FString>* targetArray = nullptr;

			// 만족도에 따라 다른 대사 줌
			switch (grade)
			{
			case ESatisfactionGrade::HIGH:
				targetArray = &data->dailyHighSatisDialogs;
				break;
			case ESatisfactionGrade::MID:
				targetArray = &data->dailyMidSatisDialogs;
				break;
			case ESatisfactionGrade::LOW:
				targetArray = &data->dailyLowSatisDialogs;
				break;
			}

			// 만족도 높, 중, 낮 각각 10개 있다 치면 대사들 중에서도 랜덤(ex.높 - 높 대사들 10개 중 하나 출력)
			if (targetArray && targetArray->Num() > 0)
			{
				int32 randIdx = FMath::RandRange(0, targetArray->Num() - 1);
				Result.Dialogue = (*targetArray)[randIdx];
				return Result;
			}

			return Result;
		}

	}
	return Result;
}


	


