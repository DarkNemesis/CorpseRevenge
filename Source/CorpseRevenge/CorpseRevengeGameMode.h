// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CorpseRevengeGameMode.generated.h"

UCLASS(minimalapi)
class ACorpseRevengeGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACorpseRevengeGameMode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		TArray<FVector> InitialEnemyLocations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		FVector PlayerDeathLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		FVector PlayerSpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool isPlayerDead;
};