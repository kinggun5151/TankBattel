// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloding,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint ;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.0f;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Locked;

private:
	void RotateBarrelAndTurret(FVector AimingDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 3.0f;

	double LastTimeFire = 0;

};
