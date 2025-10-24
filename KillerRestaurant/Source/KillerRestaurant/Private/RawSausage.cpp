// Fill out your copyright notice in the Description page of Project Settings.


#include "RawSausage.h"
#include "GrilledSausage.h"

ARawSausage::ARawSausage()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	SetRootComponent(smComp);

	smComp->SetRelativeScale3D(FVector(1.25));


}

void ARawSausage::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(-10, 67, 94));
}

void ARawSausage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


