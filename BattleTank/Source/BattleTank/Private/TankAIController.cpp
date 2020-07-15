// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerController = GetWorld()->GetFirstPlayerController();

	if (!playerController) return nullptr;

	auto pawn = playerController->GetPawn();

	if (!pawn) return nullptr;

	return Cast<ATank>(pawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank *AITank = GetAIControlledTank();
	ATank *PlayerTank = GetPlayerTank();

	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("Error, AI Tank Controller not possessing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller possessing: %s"), *(AITank->GetName()));
	}

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Error, AI Tank Controller could not find Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, 
			Warning, 
			TEXT("AI Tank Controller possessing %s found player Tank: %s"), 
			*(AITank->GetName()), 
			*(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
