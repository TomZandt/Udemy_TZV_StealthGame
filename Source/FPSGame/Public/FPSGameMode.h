// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

// Forward Declarations
class APawn;

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	// Called when mission is complete
	// @InstigatorPawn - The pawn that instigated the mission complete
	void CompleteMission(APawn* InstigatorPawn);

	// Auto called when mission is complete (Implemented in Blueprint)
	// @InstigatorPawn - The pawn that instigated the mission complete
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void bpCompleteMission(APawn* InstigatorPawn);
};



