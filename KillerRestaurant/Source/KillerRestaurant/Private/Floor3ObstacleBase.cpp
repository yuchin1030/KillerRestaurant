// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor3ObstacleBase.h"
#include "Kismet/KismetSystemLibrary.h" 
#include <Kismet/GameplayStatics.h>
#include "KillerRestaurantCharacter.h"

AFloor3ObstacleBase::AFloor3ObstacleBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFloor3ObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AKillerRestaurantCharacter>((UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
}

void AFloor3ObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor3ObstacleBase::OnObstacleOverlapDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		// 데미지처리
 
		if (player)
			player->TakeDamage(ObstacleInfo.damage);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is NULL or not have player tag"));
	}
}

void AFloor3ObstacleBase::OnObstacleOverlapInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		if (player)
			player->currentOverlappedInteractItem = this;

		UE_LOG(LogTemp, Warning, TEXT("InteractItem: %s"), *player->currentOverlappedInteractItem->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is NULL or not have player tag"));
	}
}

void AFloor3ObstacleBase::OnObstacleOverlapInteractEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	player->currentOverlappedInteractItem = nullptr;
}

