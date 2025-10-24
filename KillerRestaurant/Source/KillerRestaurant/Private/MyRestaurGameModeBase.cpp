// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRestaurGameModeBase.h"
#include "KillerRestaurantCharacter.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/SpringArmComponent.h"
#include "CustomerManager.h"

AMyRestaurGameModeBase::AMyRestaurGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyRestaurGameModeBase::BeginPlay()
{
    Super::BeginPlay();

	player = Cast<AKillerRestaurantCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

    // 가게 운영 하는 동안에는 못 움직이게
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }

	if (player)
	{
        // 초기 카메라 세팅
        player->GetCameraBoom()->TargetArmLength = 0;
		player->GetFollowCamera()->SetRelativeLocation(FVector(320, 0, 144));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player is null"));
	}

    cuM = Cast<ACustomerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerManager::StaticClass()));

}

void AMyRestaurGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bClosingTime)
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
                bClosingTime = true;
                cuM->SetClosing();
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("%02d:%02d"), gameHour, gameMinute);

    }
    
    
}
