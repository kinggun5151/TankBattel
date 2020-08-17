// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


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
	AimingComponent->Fire();
	MoveToActor(PlayerTank, AcceptanceRadius);

}

