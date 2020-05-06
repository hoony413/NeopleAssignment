// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeopleAssignmentGameMode.h"
#include "NeopleAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANeopleAssignmentGameMode::ANeopleAssignmentGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
