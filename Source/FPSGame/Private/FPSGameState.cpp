// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	// Get all the pawns in the game
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		// Get a reference to the current pawn
		APawn* Pawn = It->Get();

		// If there is a pawn and its locally controlled
		if (Pawn && Pawn->IsLocallyControlled())
		{
			// Disable input
			Pawn->DisableInput(nullptr);
		}
	}
}
