// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElavationChang = RelativeSpeed * MaxDegreesPerSecend * GetWorld()->DeltaTimeSeconds;
	auto PitchNewElevation = GetRelativeRotation().Pitch + ElavationChang;
	PitchNewElevation=FMath::Clamp<float>(PitchNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(PitchNewElevation, 0, 0));
}