// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerTargetPoint.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

ACustomerTargetPoint::ACustomerTargetPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	orderTargetPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("orderTargetPoint"));
	exitFrontTargetPint = CreateDefaultSubobject<UArrowComponent>(TEXT("exitFrontTargetPint"));
	exitRightTargetPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("exitRightTargetPoint"));

	SetRootComponent(sceneComp);
	orderTargetPoint->SetupAttachment(sceneComp);
	exitFrontTargetPint->SetupAttachment(sceneComp);
	exitRightTargetPoint->SetupAttachment(sceneComp);
}

void ACustomerTargetPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomerTargetPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

