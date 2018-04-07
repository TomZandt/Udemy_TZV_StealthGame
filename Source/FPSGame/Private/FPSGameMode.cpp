// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	// If there is a pawn...
	if (InstigatorPawn)
	{
		// Disable its input.
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);

			// If there is at least 1 view target...
			if (ReturnedActors.Num() > 0)
			{
				// Target equals the first entry.
				AActor* NewViewTarget = ReturnedActors[0];

				// Get a reference to the player controller
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				// If there is a player controller...
				if (PC)
				{
					// Blend to the new view target.
					PC->SetViewTargetWithBlend(NewViewTarget, 1.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("##_TZV_## - (FPSGameMode.cpp) - SpectatingViewPointClass is nullptr. Cannot change spectating view target."))
		}
	}

	// Auto call the BP version
	bpCompleteMission(InstigatorPawn);
}