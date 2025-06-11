// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor2_RotateItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AFloor2_RotateItemBase::AFloor2_RotateItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	SetRootComponent(sceneComp);

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	smComp->SetupAttachment(sceneComp);
}

void AFloor2_RotateItemBase::BeginPlay()
{
	Super::BeginPlay();


	
}

void AFloor2_RotateItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator newRot = FMath::RInterpTo(GetActorRotation(), targetRot, DeltaTime, 8);
	SetActorRotation(newRot);
}

void AFloor2_RotateItemBase::ChangeRot()
{
	cnt = (cnt + 1) % 4;

	targetRot = FRotator(0,0, cnt * 90);



	//switch (cnt %= 4)
	//{
	//case 0:
	//	
	//	//SetActorRotation(FRotator(0, 0, 90));
	//	break;
	//case 1:
	//	SetActorRotation(FRotator(0, 0, 180));
	//	break;
	//case 2:
	//	SetActorRotation(FRotator(0, 0, 270));
	//	break;
	//case 3:
	//	SetActorRotation(FRotator(0, 0, 0));
	//	break;
	//default:
	//	break;
	//}
}

