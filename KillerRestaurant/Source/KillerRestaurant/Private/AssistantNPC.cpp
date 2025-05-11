// Fill out your copyright notice in the Description page of Project Settings.


#include "AssistantNPC.h"
#include "Kismet/GameplayStatics.h"

AAssistantNPC::AAssistantNPC()
{
	SpeakerName = "Assistant";
}

void AAssistantNPC::StartInteract()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("PizzaRestaurant"));	// FName()에 꼭 가두기!!
}
