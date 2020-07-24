// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable,Category=Setup)
		void SetBarrelRefrence(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretRefrence(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditAnyWhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditAnyWhere, Category = Firing)
		float LaunchSpeed = 100000.0f;
	
	void AimAt(FVector HitLocation);

private:
	UTankBarrel* Barrel = nullptr;

};
