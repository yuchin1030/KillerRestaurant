// Fill out your copyright notice in the Description page of Project Settings.


#include "MerchantNPC.h"

AMerchantNPC::AMerchantNPC()
{
	PrimaryActorTick.bCanEverTick = true;

	SpeakerName = "Merchant";
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
	
}

