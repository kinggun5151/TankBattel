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
	Locked,
	OutOfAmmo
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
		float LaunchSpeed = 20000.0f;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		int GetAmmoLeft() const;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		int AmmoLeft = 3;
	EFiringState GetFiringState() const;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloding;

private:
	void RotateBarrelAndTurret(FVector AimingDirectionVector);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override ;


	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	bool IsAiming();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 3.0f;

	double LastTimeFire = 0;
	FVector AimingDirection;

	


};
