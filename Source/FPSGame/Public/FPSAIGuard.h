// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

// Forward Declare
class UPawnSensingComponent;
class APawn;
class AActor;

UENUM(BlueprintType)
enum class EAIState : uint8 
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	// Holds the original rotation of the guard
	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	// Resets the orientation to the original rotation
	UFUNCTION()
	void ResetOrientation();

	// Holds the guards state
	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIState GuardState;

	// Sets the state of the guard
	void SetGuardState(EAIState NewState);

	// Called only on clients
	UFUNCTION()
	void OnRep_GuardState();

	// Called if the guards states changes
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

	// Let the guard go on patrol
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	// First patrol point
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	// Second patrol point
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	// The current point the actor is moving to or standing at
	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
