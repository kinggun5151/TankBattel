// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"


EFiringState UTankAimingComponent::GetFiringState() const { return FiringState; }
int  UTankAimingComponent::GetAmmoLeft() const { return AmmoLeft; }

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastTimeFire = FPlatformTime::Seconds();
	

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType,  ThisTickFunction);

	if (AmmoLeft < 1)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastTimeFire) < ReloadTime)
	{
		FiringState = EFiringState::Reloding;
	}
	else if (IsAiming())
	{
		FiringState = EFiringState::Aiming;

	}
	else
	{
		FiringState = EFiringState::Locked;
	}
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
		AimingDirection = OutLaunchVolocity.GetSafeNormal();
		RotateBarrelAndTurret(AimingDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (ensure(Barrel && ProjectileBlueprint) && FiringState != EFiringState::Reloding && FiringState != EFiringState::OutOfAmmo)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeFire = FPlatformTime::Seconds();
		AmmoLeft--;
	}
}

void UTankAimingComponent::RotateBarrelAndTurret(FVector AimingDirectionVector)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimingDirectionVector.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	Barrel->Elevate(DeltaRotator.Pitch);
}

bool UTankAimingComponent::IsAiming()
{
	if (!ensure(Barrel)) { return false; }
	auto ForwardVector = Barrel->GetForwardVector();

	return !ForwardVector.Equals(AimingDirection, 0.02f);
}



