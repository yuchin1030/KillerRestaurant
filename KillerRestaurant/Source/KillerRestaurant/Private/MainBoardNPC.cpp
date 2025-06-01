// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBoardNPC.h"

AMainBoardNPC::AMainBoardNPC()
{
	SpeakerName = "MainBoard";
}

void AMainBoardNPC::StartInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("MainBoard"));
}