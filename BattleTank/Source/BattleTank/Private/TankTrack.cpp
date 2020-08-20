// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);


}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTracks();
	CurrentThrottel = 0;
}
void UTankTrack::SetThrottel(float Throttel)
{
	CurrentThrottel = FMath::Clamp<float>((CurrentThrottel + Throttel), -1, 1);

}

void UTankTrack::ApplySidewaysForce()
{
	auto SlipingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectAceleration = -SlipingSpeed / DeltaTime * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorectionForce = TankRoot->GetMass() * CorrectAceleration / 2;

	TankRoot->AddForce(CorectionForce);
}

void UTankTrack::DriveTracks()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottel * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

