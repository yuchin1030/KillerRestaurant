// Fill out your copyright notice in the Description page of Project Settings.


#include "CookManager.h"
#include "StretchedDough.h"
#include "GrilledSausage.h"
#include "CustomerManager.h"
#include "Customer.h"
#include <Kismet/GameplayStatics.h>

ACookManager::ACookManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACookManager::BeginPlay()
{
	Super::BeginPlay();
	
    isDoughPlaced.Init(false, 3);
    isSausagePlaced.Init(false, 3);
    spawnedBreads.Init(nullptr, 3);
    spawnedSausages.Init(nullptr, 3);

    SetActorLocation(FVector(459, -464, 94));

    cuM = Cast<ACustomerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerManager::StaticClass()));

}

void ACookManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACookManager::SpawnBread()
{
    if (!isDoughPlaced[0])
    {
        // 0번째 자리가 비어있다면
        if (bread_targetLoc1)
        {
            FVector targetLoc = bread_targetLoc1->GetActorLocation();

            PlaceBread(targetLoc, 0);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("bread_targetLoc1 is null"));
        }
    }
    else if (!isDoughPlaced[1])
    {
        // 1번째 자리가 비어있다면
        if (bread_targetLoc2)
        {
            FVector targetLoc = bread_targetLoc2->GetActorLocation();

            PlaceBread(targetLoc, 1);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("bread_targetLoc2 is null"));
        }
    }
    else if (!isDoughPlaced[2])
    {
        // 0번째 자리가 비어있다면

        if (bread_targetLoc3)
        {
            FVector targetLoc = bread_targetLoc3->GetActorLocation();

            PlaceBread(targetLoc, 2);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("bread_targetLoc3 is null"));
        }
    }
    else
    {
        // 도우를 더 이상 놓을 공간이 없다면
        UE_LOG(LogTemp, Warning, TEXT("You can place bread only maximum 3"));
    }
}

void ACookManager::PlaceBread(FVector b_targetLoc, int32 index)
{
    FActorSpawnParameters params;

    AStretchedDough* bread = GetWorld()->SpawnActor<AStretchedDough>(stretchDough_bp, b_targetLoc, FRotator::ZeroRotator, params);

    if (bread)
    {
        bread->SetActorScale3D(FVector(0.8f));

        // 스폰됐을때 자신(빵)이 화구 어느 인덱스 위치에 스폰되어있는지 저장해둠
        bread->SetCurBreadLocIndex(index);

        spawnedBreads[index] = bread;

        isDoughPlaced[index] = true;

        UE_LOG(LogTemp, Warning, TEXT("spawn bread%d"), index);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("bread not spawn"));
    }
   
}

void ACookManager::SpawnSausage()
{
    // 0번째 자리가 비어있다면
    if (!isSausagePlaced[0])
    {
        if (sausage_targetLoc1)
        {
            FVector targetLoc = sausage_targetLoc1->GetActorLocation();

            PlaceSausage(targetLoc, 0);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("sausage_targetLoc1 is null"));
        }
    }
    // 1번째 자리가 비어있다면
    else if (!isSausagePlaced[1])
    {
        if (sausage_targetLoc2)
        {
            FVector targetLoc = sausage_targetLoc2->GetActorLocation();

            PlaceSausage(targetLoc, 1);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("sausage_targetLoc2 is null"));
        }
    }
    // 2번째 자리가 비어있다면
    else if (!isSausagePlaced[2])
    {

        if (sausage_targetLoc3)
        {
            FVector targetLoc = sausage_targetLoc3->GetActorLocation();

            PlaceSausage(targetLoc, 2);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("sausage_targetLoc3 is null"));
        }
    }
    else
    {
        // 도우를 더 이상 놓을 공간이 없다면
        UE_LOG(LogTemp, Warning, TEXT("You can place sausage only maximum 3"));
    }
}

void ACookManager::PlaceSausage(FVector s_targetLoc, int32 index)
{
    FActorSpawnParameters params;
    AGrilledSausage* sausage = GetWorld()->SpawnActor<AGrilledSausage>(grilledSausage_bp, s_targetLoc, FRotator::ZeroRotator, params);

    if (sausage)
    {
        // 스폰됐을때 자신(소세지)이 화구 어느 인덱스 위치에 스폰되어있는지 저장해둠
        sausage->SetCurSausageLocIndex(index);

        isSausagePlaced[index] = true;

        spawnedSausages[index] = sausage;

        UE_LOG(LogTemp, Warning, TEXT("spawn sausage%d"), index);

        sausage->Grill();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("sausage not spawn"));
    }
   
}

void ACookManager::InsertGrilledSausageToBread(AGrilledSausage* grilledSausage, int32 curSausageIndex)
{
    // 내가 클릭한 액터의 isGrilled 가 true인가(소세지가 구워졌는가)
    if (grilledSausage->isGrilled)
    {
        if (spawnedBreads.Num() > 0)
        {
            // 소세지가 구워졌고, 빵이 스폰되어 있다면 빵들 중 빈 곳에 순차적으로 배치
            for (int32 i = 0; i < spawnedBreads.Num(); ++i)
            {
                if (spawnedBreads[i] && !spawnedBreads[i]->bHasSausage)
                {
                    spawnedBreads[i]->sm_sausage->SetVisibility(true);
                    spawnedBreads[i]->bHasSausage = true;
                    grilledSausage->Destroy();

                    // 소세지가 사용된 자리에 해당하는 소세지 자리를 false로 설정(소세지 다시 스폰 가능하게)
                    isSausagePlaced[curSausageIndex] = false;
                    return;
                }

            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("You don't have any bread to insert sausage"));
        }
       
       
    }
    // 소세지가 탔는가
    else if (grilledSausage->isBurned)
    {
        UE_LOG(LogTemp, Warning, TEXT("Sausage burned"));
    }
    // 소세지가 아직 덜 구워졌는가
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sausage is not grilled"));
    }
}

void ACookManager::PlacePickles()
{
    if (spawnedBreads.Num() > 0)
    {
        // 소세지가 구워졌고, 빵이 스폰되어 있다면 빵들 중 빈 곳에 순차적으로 배치
        for (int32 i = 0; i < spawnedBreads.Num(); ++i)
        {
            if (spawnedBreads[i] && !spawnedBreads[i]->bHasPickles)
            {
                spawnedBreads[i]->sm_pickles->SetVisibility(true);
                spawnedBreads[i]->bHasPickles = true;

                return;
            }

        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You don't have any bread to place pickles"));
    }
}

void ACookManager::PlaceOnions()
{
    if (spawnedBreads.Num() > 0)
    {
        // 소세지가 구워졌고, 빵이 스폰되어 있다면 빵들 중 빈 곳에 순차적으로 배치
        for (int32 i = 0; i < spawnedBreads.Num(); ++i)
        {
            if (spawnedBreads[i] && !spawnedBreads[i]->bHasOnions)
            {
                spawnedBreads[i]->sm_onions->SetVisibility(true);
                spawnedBreads[i]->bHasOnions = true;

                return;
            }

        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You don't have any bread to place onions"));
    }
}

void ACookManager::PlaceKetchup()
{
    if (spawnedBreads.Num() > 0)
    {
        // 소세지가 구워졌고, 빵이 스폰되어 있다면 빵들 중 빈 곳에 순차적으로 배치
        for (int32 i = 0; i < spawnedBreads.Num(); ++i)
        {
            if (spawnedBreads[i] && !spawnedBreads[i]->bHasKetcuhp)
            {
                spawnedBreads[i]->sm_ketchup->SetVisibility(true);
                spawnedBreads[i]->bHasKetcuhp = true;

                return;
            }

        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You don't have any bread to place ketchup"));
    }
}

void ACookManager::PlaceMustard()
{
    if (spawnedBreads.Num() > 0)
    {
        // 소세지가 구워졌고, 빵이 스폰되어 있다면 빵들 중 빈 곳에 순차적으로 배치
        for (int32 i = 0; i < spawnedBreads.Num(); ++i)
        {
            if (spawnedBreads[i] && !spawnedBreads[i]->bHasMustard)
            {
                spawnedBreads[i]->sm_mustard->SetVisibility(true);
                spawnedBreads[i]->bHasMustard = true;

                return;
            }

        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You don't have any bread to place mustard"));
    }
}

void ACookManager::FinishMaking(int32 _bellNum)
{
    if (cuM->currentCustomer->customerState == ECustomerState::WAIT)
    {
        FHotdogTopping completedHotdog;

        if (spawnedBreads[_bellNum])
        {
            if (spawnedBreads.Num() > 0 && spawnedBreads[_bellNum]->bHasSausage)
            {
                completedHotdog.bPickles = spawnedBreads[_bellNum]->bHasPickles;
                completedHotdog.bOnions = spawnedBreads[_bellNum]->bHasOnions;
                completedHotdog.bKetchup = spawnedBreads[_bellNum]->bHasKetcuhp;
                completedHotdog.bMustard = spawnedBreads[_bellNum]->bHasMustard;

                Serving(_bellNum, completedHotdog, spawnedBreads[_bellNum]);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("spawnBreads is null"));
        }
        
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("can't check menu (Customer is not in WAIT state)"));
    }

}

void ACookManager::Serving(int32 bellNum_, FHotdogTopping _completedHotdog, AStretchedDough* _completedActor)
{
    // FHotdogTopping → FHotdogOrder로 변환
    FHotdogOrder converted;
    converted.bPickle = _completedHotdog.bPickles;
    converted.bOnion = _completedHotdog.bOnions;
    converted.bKetchup = _completedHotdog.bKetchup;
    converted.bMustard = _completedHotdog.bMustard;

    if (cuM->OrderedHotdogs.Contains(converted))
    {
        // 서빙해야할 각 핫도그 메뉴의 개수가 남아있을 경우
        if (cuM->OrderedHotdogs[converted] > 0)
        {
            // 해당 메뉴 개수 -1
            cuM->OrderedHotdogs[converted]--;

            _completedActor->Destroy();

            // 빵이 사용된 자리를 false로 설정(빵 다시 스폰 가능하게)
            isDoughPlaced[bellNum_] = false;
            //spawnedBreads[bellNum_] = nullptr;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("already serving done. serve different menu"));
            return;
        }

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("It's not in order"));
        return;
    }

    // 모든 핫도그 서빙 완료 여부 확인
    bool bAllDone = true;
    for (const auto& orderHotdog : cuM->OrderedHotdogs)
    {
        if (orderHotdog.Value > 0)
        {
            bAllDone = false;
            break;
        }
    }

    // 서빙 다 했으면
    if (bAllDone)
    {
        UE_LOG(LogTemp, Warning, TEXT("Serving all done"));
        cuM->currentCustomer->customerState = ECustomerState::CHECK;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You have to serve more"));
    }
}