// Fill out your copyright notice in the Description page of Project Settings.


#include "MerchantNPC.h"
#include "Kismet/GameplayStatics.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Start Interact with merchantNPC"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("PizzaRestaurant"));	// FName()에 꼭 가두기!!
	
	 //대화 UI창

}

