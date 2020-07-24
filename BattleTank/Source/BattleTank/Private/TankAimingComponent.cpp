// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	FVector OutLaunchVolocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSoulotion = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVolocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSoulotion)
	{
		auto AimingDirection = OutLaunchVolocity.GetSafeNormal();
		RotateBarrelAndTurret(AimingDirection);
	}
}

void UTankAimingComponent::SetBarrelRefrence(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
void UTankAimingComponent::SetTurretRefrence(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::RotateBarrelAndTurret(FVector AimingDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimingDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("Elevated at %f"), DeltaRotator.Pitch);

	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);//
}