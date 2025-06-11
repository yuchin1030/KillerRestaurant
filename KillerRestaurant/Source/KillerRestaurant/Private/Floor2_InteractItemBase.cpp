// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor2_InteractItemBase.h"
#include <Kismet/GameplayStatics.h>

AFloor2_InteractItemBase::AFloor2_InteractItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFloor2_InteractItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFloor2_InteractItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor2_InteractItemBase::ChangeCameraView()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetViewTargetWithBlend(this, 0.5f); // 이 액터로 카메라 뷰 전환

		// 플레이어 시선 및 이동 막기(true) 또는 활성화(false)
		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);
	};
}

