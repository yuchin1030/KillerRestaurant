// Fill out your copyright notice in the Description page of Project Settings.


#include "MerchantNPC.h"

// Sets default values
AMerchantNPC::AMerchantNPC()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMerchantNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMerchantNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMerchantNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMerchantNPC::StartInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Interact with merchantNPC"));
}

