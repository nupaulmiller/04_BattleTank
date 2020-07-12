// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControllerTank = GetControlledTank();

	if (!ControllerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Error, Player Controller not possessing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *(ControllerTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}


bool ATankPlayerController::GetSightRayHitLocation(OUT FVector &HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	FVector LookDirection;
	
	GetViewportSize(OUT ViewPortSizeX, OUT ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, 
		ViewPortSizeY * CrossHairYLocation);

	if (GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *LookDirection.ToString());
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		OUT WorldLocation, 
		OUT LookDirection);
}
