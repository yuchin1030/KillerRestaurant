// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRestaurGameModeBase.h"
#include "KillerRestaurantCharacter.h"
#include "Camera/CameraComponent.h"

AMyRestaurGameModeBase::AMyRestaurGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyRestaurGameModeBase::BeginPlay()
{
    Super::BeginPlay();

	player = Cast<AKillerRestaurantCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player)
	{
		player->GetFollowCamera()->SetRelativeLocation(FVector(410, 0, 80));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player is null"));
	}
}

void AMyRestaurGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bRestaurantClosed)
        return;

    timeElapsed += DeltaTime;

    // 게임 시간으로 1분이 경과한 경우
    if (timeElapsed >= timeSpeed * 10)
    {
        gameMinute += 10;
        timeElapsed = 0;

        // 60분이 경과하면 시간 증가
        if (gameMinute >= 60)
        {
            gameMinute = 0;
            gameHour++;


            // 18시가 되면 손님 더 이상 들어오지 않음
            if (gameHour >= 18)
            {
                gameHour = 18;  // 18시로 고정
                gameMinute = 0; // 00분으로 고정
                // 손님이 더 이상 들어오지 않도록 처리
                bRestaurantClosed = true;

            }
        }
        UE_LOG(LogTemp, Warning, TEXT("%02d:%02d"), gameHour, gameMinute);

    }
    
    
}
