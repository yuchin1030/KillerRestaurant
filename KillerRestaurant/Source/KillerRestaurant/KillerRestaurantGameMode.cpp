// Copyright Epic Games, Inc. All Rights Reserved.

#include "KillerRestaurantGameMode.h"
#include "KillerRestaurantCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKillerRestaurantGameMode::AKillerRestaurantGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
