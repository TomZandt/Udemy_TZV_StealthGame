// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and name
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	// Make MeshComp the root component and attach the sphere to it
	RootComponent = MeshComp;
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

