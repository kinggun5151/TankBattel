// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
		ATank* GetControlledTank() const;
private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXlocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYlocation = 0.3333f;
	UPROPERTY(EditDefaultsOnly)
		int LineTraceRang = 1000000;

	
};
