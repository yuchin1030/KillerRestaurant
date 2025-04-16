// Fill out your copyright notice in the Description page of Project Settings.


#include "CookManager.h"
#include "StretchedDough.h"
#include "GrilledSausage.h"

ACookManager::ACookManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACookManager::BeginPlay()
{
	Super::BeginPlay();
	
    isDoughPlaced.Init(false, 3);
    isSausagePlaced.Init(false, 3);

    SetActorLocation(FVector(459, -464, 94));
}

void ACookManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACookManager::SpawnBread()
{
    if (!isDoughPlaced[0])
    {
        // 0��° �ڸ��� ����ִٸ�
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
        // 1��° �ڸ��� ����ִٸ�
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
        // 0��° �ڸ��� ����ִٸ�

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
        // ���츦 �� �̻� ���� ������ ���ٸ�
        UE_LOG(LogTemp, Warning, TEXT("You can place bread only maximum 3"));
    }
}

void ACookManager::PlaceBread(FVector b_targetLoc, int32 index)
{
    FActorSpawnParameters params;

    AStretchedDough* bread = GetWorld()->SpawnActor<AStretchedDough>(stretchDough_bp, b_targetLoc, FRotator::ZeroRotator, params);

    if (bread)
    {
        // ���������� �ڽ�(��)�� ȭ�� ��� �ε��� ��ġ�� �����Ǿ��ִ��� �����ص�
        bread->SetCurBreadLocIndex(index);

        spawnedBreads.Add(bread);

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
    // 0��° �ڸ��� ����ִٸ�
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
    // 1��° �ڸ��� ����ִٸ�
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
    // 2��° �ڸ��� ����ִٸ�
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
        // ���츦 �� �̻� ���� ������ ���ٸ�
        UE_LOG(LogTemp, Warning, TEXT("You can place sausage only maximum 3"));
    }
}

void ACookManager::PlaceSausage(FVector s_targetLoc, int32 index)
{
    FActorSpawnParameters params;
    AGrilledSausage* sausage = GetWorld()->SpawnActor<AGrilledSausage>(grilledSausage_bp, s_targetLoc, FRotator::ZeroRotator, params);

    if (sausage)
    {
        // ���������� �ڽ�(�Ҽ���)�� ȭ�� ��� �ε��� ��ġ�� �����Ǿ��ִ��� �����ص�
        sausage->SetCurSausageLocIndex(index);

        isSausagePlaced[index] = true;

        spawnedSausages.Add(sausage);

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
    // ���� Ŭ���� ������ isGrilled �� true�ΰ�(�Ҽ����� �������°�)
    if (grilledSausage->isGrilled)
    {
        if (spawnedBreads.Num() > 0)
        {
            // �Ҽ����� ��������, ���� �����Ǿ� �ִٸ� ���� �� �� ���� ���������� ��ġ
            for (int32 i = 0; i < spawnedBreads.Num(); ++i)
            {
                if (spawnedBreads[i] && !spawnedBreads[i]->bHasSausage)
                {
                    spawnedBreads[i]->sm_sausage->SetVisibility(true);
                    spawnedBreads[i]->bHasSausage = true;
                    grilledSausage->Destroy();

                    // �Ҽ����� ���� �ڸ��� �ش��ϴ� �Ҽ��� �ڸ��� false�� ����(�Ҽ��� �ٽ� ���� �����ϰ�)
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
    // �Ҽ����� ���°�
    else if (grilledSausage->isBurned)
    {
        UE_LOG(LogTemp, Warning, TEXT("Sausage burned"));
    }
    // �Ҽ����� ���� �� �������°�
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sausage is not grilled"));
    }
}

void ACookManager::PlacePickles()
{
    if (spawnedBreads.Num() > 0)
    {
        // �Ҽ����� ��������, ���� �����Ǿ� �ִٸ� ���� �� �� ���� ���������� ��ġ
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
        // �Ҽ����� ��������, ���� �����Ǿ� �ִٸ� ���� �� �� ���� ���������� ��ġ
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
        // �Ҽ����� ��������, ���� �����Ǿ� �ִٸ� ���� �� �� ���� ���������� ��ġ
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
        // �Ҽ����� ��������, ���� �����Ǿ� �ִٸ� ���� �� �� ���� ���������� ��ġ
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

