// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ensure(PlayerTank && AimingComponent)) { return; }
	
	AimingComponent->AimAt(PlayerTank->GetTargetLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesdTank = Cast<ATank>(InPawn);
		if (!ensure(PossesdTank)) { return; }

		PossesdTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesdTankDeath);
	}

}

void ATankAIController::OnPossesdTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}