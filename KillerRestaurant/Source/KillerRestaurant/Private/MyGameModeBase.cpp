// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "KillerRestaurantCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMyGameModeBase::AMyGameModeBase()
{
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AKillerRestaurantCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player)
	{
		//player->GetCameraBoom()->SocketOffset = FVector(0.f, 125.f, 100.f); // Y축 오른쪽으로 125만큼, Z축 위로 100만큼 오프셋
		//player->GetCameraBoom()->TargetArmLength = 300.f;
		//player->GetCameraBoom()->bUsePawnControlRotation = true;
		//player->GetCameraBoom()->bInheritPitch = true;
		//player->GetCameraBoom()->bInheritYaw = true;
		//player->GetCameraBoom()->bInheritRoll = true;

		//// FollowCamera 설정
		//player->GetFollowCamera()->bUsePawnControlRotation = false;

		// 캐릭터 회전 설정
		/*player->bUseControllerRotationYaw = true;
		player->GetCharacterMovement()->bOrientRotationToMovement = false;*/
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player is null"));
	}
}
