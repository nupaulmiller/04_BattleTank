// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"



ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* AITankController = GetAIControlledTank();

	if (!AITankController)
	{
		UE_LOG(LogTemp, Error, TEXT("Error, AI Tank Controller not possessing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller possessing: %s"), *(AITankController->GetName()));
	}
}
