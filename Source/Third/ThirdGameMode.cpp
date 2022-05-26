// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdGameMode.h"
#include "ThirdCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThirdGameMode::AThirdGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
