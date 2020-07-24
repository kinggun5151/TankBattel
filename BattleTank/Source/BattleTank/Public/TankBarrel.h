// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxDegreesPerSecend = 10;

	UPROPERTY(EditAnyWhere, Category = Setup)
		float MinElevation = 0;

	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxElevation = 40;

};