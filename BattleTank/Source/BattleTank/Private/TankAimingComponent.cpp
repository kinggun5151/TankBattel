// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure (Barrel&& Turret)) { return; }
	
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

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::RotateBarrelAndTurret(FVector AimingDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimingDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);//
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastTimeFire) > ReloadTime;
	if (ensure(Barrel && ProjectileBlueprint) && isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeFire = FPlatformTime::Seconds();
	}
}