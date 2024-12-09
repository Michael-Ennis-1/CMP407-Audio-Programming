// Copyright Epic Games, Inc. All Rights Reserved.

#include "CMP407ProjectGameMode.h"
#include "CMP407ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACMP407ProjectGameMode::ACMP407ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
