// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ControlledTank = Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerTank && ControlledTank)
	{
		ControlledTank->AimAt(PlayerTank->GetTargetLocation());
		ControlledTank->Fire();
	}
	
	MoveToActor(PlayerTank, AcceptanceRadius);

}

