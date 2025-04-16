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

    spawnedBreads.Add(bread);

    isDoughPlaced[index] = true;

    UE_LOG(LogTemp, Warning, TEXT("spawn bread%d"), index);
}

void ACookManager::SpawnSausage()
{
    if (!isSausagePlaced[0])
    {
        // 0��° �ڸ��� ����ִٸ�
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
    else if (!isSausagePlaced[1])
    {
        // 1��° �ڸ��� ����ִٸ�
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
    else if (!isSausagePlaced[2])
    {
        // 2��° �ڸ��� ����ִٸ�

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

    isSausagePlaced[index] = true;

    spawnedSausages.Add(sausage);

    UE_LOG(LogTemp, Warning, TEXT("spawn sausage%d"), index);

    sausage->Grill();
}

void ACookManager::InsertGrilledSausageToBread(AGrilledSausage* grilledSausage)
{
    // ���� Ŭ���� ������ isGrilled �� true�ΰ�
    if (grilledSausage->isGrilled && !grilledSausage->isBurned)
    {
        // true��� ���� �� �� ���� ���������� ��ġ
        if (spawnedBreads[0] && !spawnedBreads[0]->bHasSausage)
        {
            spawnedBreads[0]->sm_sausage->SetVisibility(true);
            spawnedBreads[0]->bHasSausage = true;
            grilledSausage->Destroy();

            // �Ҽ��� �ٽ� ���� �����ϰ�
            isSausagePlaced[0] = false;
        }
        else if (spawnedBreads[1] && !spawnedBreads[1]->bHasSausage)
        {
            spawnedBreads[1]->sm_sausage->SetVisibility(true);
            spawnedBreads[1]->bHasSausage = true;
            grilledSausage->Destroy();

            isSausagePlaced[1] = false;
        }
        else if (spawnedBreads[2] && !spawnedBreads[2]->bHasSausage)
        {
            spawnedBreads[2]->sm_sausage->SetVisibility(true);
            spawnedBreads[2]->bHasSausage = true;
            grilledSausage->Destroy();

            isSausagePlaced[2] = false;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("You don't have any bread to insert sausage"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sausage is not grilled"));
    }
}

