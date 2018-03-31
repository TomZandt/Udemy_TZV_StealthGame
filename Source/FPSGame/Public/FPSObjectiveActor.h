// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

// Forward Declare
class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * MeshComp;	// Create a mesh component to visually show the objective.

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;		// Create a sphere component for collision.

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
