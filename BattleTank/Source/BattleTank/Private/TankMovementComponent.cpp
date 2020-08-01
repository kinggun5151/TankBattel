//Completed

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* Track_LToSet, UTankTrack* Track_RToSet)
{
	Track_L = Track_LToSet;
	Track_R = Track_RToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntetion = MoveVelocity.GetSafeNormal();

	auto ThrowForward = FVector::DotProduct(TankForward, AIForwardIntetion);
	IntendMoveForward(ThrowForward);

	auto ThrowRight = FVector::CrossProduct(TankForward, AIForwardIntetion).Z;
	IntendMoveRight(ThrowRight);

}
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!Track_L || !Track_R) { return; }
	Track_L->SetThrottel(Throw);
	Track_R->SetThrottel(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!Track_L || !Track_R) { return; }
	Track_L->SetThrottel(Throw);
	Track_R->SetThrottel(-Throw);
}