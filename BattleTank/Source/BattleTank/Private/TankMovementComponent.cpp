// Fill out your copyright notice in the Description page of Project Settings.
#include <Logging/LogMacros.h>
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward Throw: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* Left, UTankTrack* Right)
{
	if (!Left || !Right)
	{
		UE_LOG(LogUObjectGlobals, Fatal, TEXT("Could not Initialize Movement Component because Left and Right Track references are not valid"));
		return;
	}

	LeftTrack = Left;
	RightTrack = Right;
}
