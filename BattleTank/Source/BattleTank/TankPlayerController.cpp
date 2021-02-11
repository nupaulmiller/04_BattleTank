// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "TankControllerBase.h"
#include "TankAimingComponent.h"
#include "Tank.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATankPlayerController::ATankPlayerController() 
{
	UE_LOG(LogTemp, Error, TEXT("Saith_ControllerConstruction"));
	ControllerName = FString("Player Controller");
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Saith_7"));
	ATank* ControllerTank = GetControlledTank();

	if (!ControllerTank)
	{
		auto AimingComponent = ControllerTank->FindComponentByClass<UTankAimingComponent>();

		if (AimingComponent)
			FoundAimingComponent(AimingComponent);
		else
			UE_LOG(LogTemp, Warning, TEXT("Player Controller could not Find Aiming Component"));
	}


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
		if (!GetControlledTank()->TankAimingComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Saith_TankAimingComponent"));
			return;
		}
		GetControlledTank()->TankAimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector &HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	FVector LookDirection;

	GetViewportSize(OUT ViewPortSizeX, OUT ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	if (GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		return GetLookVectorHitLocation(OUT HitLocation, LookDirection);
	}

	return false;
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

bool ATankPlayerController::GetLookVectorHitLocation(OUT FVector &HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	//UE_LOG(LogTemp, Warning, TEXT("StartLocation: %s"), *StartLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("EndLocation: %s"), *EndLocation.ToString());

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitResult: %s"), *HitResult.ToString());
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);

	return false;
}