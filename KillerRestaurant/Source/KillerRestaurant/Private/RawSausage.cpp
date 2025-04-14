// Fill out your copyright notice in the Description page of Project Settings.


#include "RawSausage.h"
#include "GrilledSausage.h"

// Sets default values
ARawSausage::ARawSausage()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);

	smComp->OnClicked.AddDynamic(this, &ARawSausage::OnClicked);
}

void ARawSausage::BeginPlay()
{
	Super::BeginPlay();
	
	isSausagePlaced.Init(false, 3);
}

void ARawSausage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARawSausage::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
    if (!isSausagePlaced[0])
    {
        // 0번째 자리가 비어있다면
        if (A_targetLoc1)
        {
            FVector targetLoc = A_targetLoc1->GetActorLocation();

            PlaceSausage(targetLoc, 0);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("A_targetLoc1 is null"));
        }
    }
    else if (!isSausagePlaced[1])
    {
        // 1번째 자리가 비어있다면
        if (A_targetLoc2)
        {
            FVector targetLoc = A_targetLoc2->GetActorLocation();

            PlaceSausage(targetLoc, 1);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("A_targetLoc2 is null"));
        }
    }
    else if (!isSausagePlaced[2])
    {
        // 0번째 자리가 비어있다면

        if (A_targetLoc3)
        {
            FVector targetLoc = A_targetLoc3->GetActorLocation();

            PlaceSausage(targetLoc, 2);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("A_targetLoc3 is null"));
        }
    }
    else
    {
        // 도우를 더 이상 놓을 공간이 없다면
        UE_LOG(LogTemp, Warning, TEXT("You can place sausage only maximum 3"));
    }
}

void ARawSausage::PlaceSausage(FVector targetLoc, int32 index)
{
    FActorSpawnParameters params;
    AGrilledSausage* grilledSausage = GetWorld()->SpawnActor<AGrilledSausage>(grilledSausage_bp, targetLoc, FRotator::ZeroRotator, params);

    isSausagePlaced[index] = true;

    UE_LOG(LogTemp, Warning, TEXT("spawn sausage%d"), index);

    grilledSausage->Grill(index);
}


