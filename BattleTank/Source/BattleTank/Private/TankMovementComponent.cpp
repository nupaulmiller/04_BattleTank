// Fill out your copyright notice in the Description page of Project Settings.
#include <Logging/LogMacros.h>
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward Throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward Throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* Left, UTankTrack* Right)
{
	checkf((Left && Right), TEXT("Error Initializing Movement Component: Track references are not valid"));

	LeftTrack = Left;
	RightTrack = Right;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	//No need to call super because we are replacing logic
	auto TankForwardFector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("Request Direct Move By %s at Velocity: %s"), *TankNameForLog, *VelocityForLog);
	auto ForwardThrow = FVector::DotProduct(TankForwardFector, AIForwardIntention);
	auto HorizontalThrow = FVector::CrossProduct(TankForwardFector, AIForwardIntention);

	IntendMoveForward(ForwardThrow);
    IntendTurnRight(HorizontalThrow.Z);
}
