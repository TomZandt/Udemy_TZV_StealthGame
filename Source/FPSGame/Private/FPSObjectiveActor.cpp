// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "FPSCharacter.h"


// *************************************************************************************************
// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

	// Tell server
	SetReplicates(true);
}

// *************************************************************************************************
// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
}

// *************************************************************************************************
void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

// *************************************************************************************************
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Play base that we are overriding using super::
	Super::NotifyActorBeginOverlap(OtherActor);

	// Implement our own override:
	PlayEffects();

	// If i am the server
	if (Role == ROLE_Authority)
	{
		// If my actor has collided...
		AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
		if (MyCharacter)
		{
			// Set carrying to true
			MyCharacter->bIsCarryingObjective = true;

			// Destroy objective actor
			Destroy();
		}
	}
}

