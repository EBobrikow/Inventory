// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Actors/InventGameMode.h"
#include "Core/Actors/InventCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventGameMode::AInventGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
