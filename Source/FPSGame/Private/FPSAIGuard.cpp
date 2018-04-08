// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "AI/Navigation/NavigationSystem.h"

// *************************************************************************************************
// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	GuardState = EAIState::Idle;	
}

// *************************************************************************************************
// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	// Store the original rotation
	OriginalRotation = GetActorRotation();

	// Check to see if we are supposed to be patrolling
	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

// *************************************************************************************************
void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	// Debug
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	// Get the game mode (single player only)
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}

	// Set guard state to alerted
	SetGuardState(EAIState::Alerted);

	// Stop patrolling
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
}

// *************************************************************************************************
void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	// If im alerted..
	if (GuardState == EAIState::Alerted)
	{
		// Return
		return;
	}

	// Debug
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	// Create vector direction and normalise
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	// Create a rotator for the new look at (zero out pitch and roll)
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	// Set the new rotation
	SetActorRotation(NewLookAt);

	// Reset timer and reset orientation after 3 seconds
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);

	SetGuardState(EAIState::Suspicious);

	// Stop patrolling
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
}

// *************************************************************************************************
void AFPSAIGuard::ResetOrientation()
{
	// If im alerted..
	if (GuardState == EAIState::Alerted)
	{
		// Return
		return;
	}

	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);

	// Patrolling has stopped, if were are a patrolling pawn, pick a new point
	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

// *************************************************************************************************
void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	// If the states are the same...
	if (GuardState == NewState)
	{
		// Return
		return;
	}

	// Set to new state
	GuardState = NewState;

	// Call on state changed for blueprint
	OnStateChanged(GuardState);
}

// *************************************************************************************************
void AFPSAIGuard::MoveToNextPatrolPoint()
{
	// Assign to next patrol point
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UNavigationSystem::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}

// *************************************************************************************************
// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Patrol Goal Checks
	if (CurrentPatrolPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();

		// Check to see if we are within 200 units of our goal, otherwise pick a new one
		if (DistanceToGoal < 200)
		{
			MoveToNextPatrolPoint();
		}
	}
}

