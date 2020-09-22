// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	if (!GetPawn()) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;

	if ((GetSightRayHitLocation(HitLocation)))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXlocation, ViewPortSizeY * CrossHairYlocation);

	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation,LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
		return true;
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult Hit;
	auto Start = PlayerCameraManager->GetCameraLocation();
	auto End = Start + (LookDirection * LineTraceRang);

	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = Hit.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesdTank = Cast<ATank>(InPawn);
		if (!ensure(PossesdTank)) { return; }

		PossesdTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesdTankDeath);
	}

}

void ATankPlayerController::OnPossesdTankDeath()
{
	StartSpectatingOnly();
}