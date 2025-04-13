// Fill out your copyright notice in the Description page of Project Settings.


#include "Dough.h"
#include "Components/StaticMeshComponent.h"
#include "StretchedDough.h"

ADough::ADough()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
    SetRootComponent(smComp);

	smComp->OnClicked.AddDynamic(this, &ADough::OnClicked);
}

void ADough::BeginPlay()
{
	Super::BeginPlay();
	
    isDoughPlaced.Init(false, 3);

    SetActorLocation(FVector(459, -464, 94));
}

void ADough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADough::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
    if (!isDoughPlaced[0])
    {
        // 0번째 자리가 비어있다면
        if (A_targetLoc1)
        {
            FVector targetLoc = A_targetLoc1->GetActorLocation();

            FActorSpawnParameters params;

            AStretchedDough* stretchDough = GetWorld()->SpawnActor<AStretchedDough>(stretchDough_bp, targetLoc, FRotator::ZeroRotator, params);

            isDoughPlaced[0] = true;
            
            UE_LOG(LogTemp, Warning, TEXT("spawn dough1"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("A_targetLoc1 is null"));
        }
    }
    else if (!isDoughPlaced[1])
    {
        // 1번째 자리가 비어있다면
        if (A_targetLoc2)
        {
            FVector targetLoc = A_targetLoc2->GetActorLocation();

            FActorSpawnParameters params;

            AStretchedDough* stretchDough = GetWorld()->SpawnActor<AStretchedDough>(stretchDough_bp, targetLoc, FRotator::ZeroRotator, params);

            isDoughPlaced[1] = true;

            UE_LOG(LogTemp, Warning, TEXT("spawn dough2"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("A_targetLoc2 is null"));
        }
    }
    else if (!isDoughPlaced[2])
    {
        // 0번째 자리가 비어있다면

        if (A_targetLoc3)
        {
            FVector targetLoc = A_targetLoc3->GetActorLocation();

            FActorSpawnParameters params;

            AStretchedDough* stretchDough = GetWorld()->SpawnActor<AStretchedDough>(stretchDough_bp, targetLoc, FRotator::ZeroRotator, params);

            isDoughPlaced[2] = true;

            UE_LOG(LogTemp, Warning, TEXT("spawn dough3"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("A_targetLoc3 is null"));
        }
    }
    else
    {
        // 도우를 더 이상 놓을 공간이 없다면
        UE_LOG(LogTemp, Warning, TEXT("You can place dough only maximum 3"));
    }
}

