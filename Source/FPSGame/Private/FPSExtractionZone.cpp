// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Create and setup a UBoxComponent
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	OverlapComponent->SetHiddenInGame(false);
	RootComponent = OverlapComponent;
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
}

// Called when overlapped
void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("##_TZV_## - Overlapped with extraction zone."));
}
