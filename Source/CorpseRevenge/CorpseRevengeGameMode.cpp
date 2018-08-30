// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CorpseRevengeGameMode.h"
#include "CorpseRevengePlayerController.h"
#include "CorpseRevengeCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Runtime/Engine/Classes/Engine/World.h"

ACorpseRevengeGameMode::ACorpseRevengeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACorpseRevengePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}