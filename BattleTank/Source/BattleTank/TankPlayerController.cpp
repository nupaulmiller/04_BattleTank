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

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller started"))
		 
}
