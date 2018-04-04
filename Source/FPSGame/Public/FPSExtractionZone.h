// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

//Forward Declarations
class UBoxComponent;
class UDecalComponent;
class USoundBase;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:
	// The overlap component for the extraction zone
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComponent;

	// Called when overlapped
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult & SweepResult);

	// Stores the sound for entering the extraction without the objective.
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;

private:
	FVector ExtractionSizeVector = { 200.0f, 200.0f, 200.0f };
};
