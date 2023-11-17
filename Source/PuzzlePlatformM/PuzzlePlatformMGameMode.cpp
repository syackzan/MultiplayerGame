// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformMGameMode.h"
#include "PuzzlePlatformMCharacter.h"
#include "UObject/ConstructorHelpers.h"


APuzzlePlatformMGameMode::APuzzlePlatformMGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
