// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChang = RelativeSpeed * MaxDegreesPerSecend * GetWorld()->DeltaTimeSeconds;
	auto YawNewRotation = GetRelativeRotation().Yaw + RotationChang;
	
	SetRelativeRotation(FRotator(0, YawNewRotation, 0));
}