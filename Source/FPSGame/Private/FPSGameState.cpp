// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"

// *************************************************************************************************
void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	// Get all the player controllers in the game
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		// Get a reference to the current player controller
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());

		// If there is a player controller and its ours
		if (PC && PC->IsLocalController())
		{
			// Call mission completed
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			// Get a reference to the current pawn
			APawn* MyPawn = PC->GetPawn();

			// If there is a pawn
			if (MyPawn)
			{
				// Disable input
				MyPawn->DisableInput(nullptr);
			}
		}
	}
}
