// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// *************************************************************************************************
// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Create and setup a UBoxComponent
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetBoxExtent(ExtractionSizeVector);
	OverlapComponent->SetHiddenInGame(false);
	RootComponent = OverlapComponent;
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	// Create and setup a DecalComponent
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->DecalSize = ExtractionSizeVector;
	DecalComponent->SetupAttachment(RootComponent);

}

// *************************************************************************************************
// Called when overlapped
void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										bool bFromSweep, const FHitResult & SweepResult)
{
	// Get pawn...
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	// If there is no pawn...
	if (MyPawn == nullptr)
	{
		// Return.
		return;
	}

	// If my pawn has the objective...
	if (MyPawn->bIsCarryingObjective)
	{
		// Get the game mode (single player only)
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->CompleteMission(MyPawn, true);
		}		
	}
	else
	{
		// Play objective missing sound
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

	// Send a log message to UE4
	UE_LOG(LogTemp, Log, TEXT("##_TZV_## - Overlapped with extraction zone."));
}
