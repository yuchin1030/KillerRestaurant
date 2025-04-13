// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRestaurGameModeBase.h"
#include "KillerRestaurantCharacter.h"
#include "Camera/CameraComponent.h"

void AMyRestaurGameModeBase::BeginPlay()
{
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
