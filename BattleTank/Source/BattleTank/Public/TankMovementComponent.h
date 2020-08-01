//Completed


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void IntendMoveRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* Track_LToSet, UTankTrack* Track_RToSet);

private:

	UTankTrack* Track_L = nullptr;
	UTankTrack* Track_R = nullptr;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

};
