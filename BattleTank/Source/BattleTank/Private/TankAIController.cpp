// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "TankControllerBase.h"
#include "TankAimingComponent.h"
#include "../Tank.h"

ATankAIController::ATankAIController()
{
	ControllerName = FString("AI Controller");
}

void ATankAIController::Tick(float DeltaTime)
{
	ATank *PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank *AICOntrolledTank = Cast<ATank>(GetPawn());

	if (PlayerTank && AICOntrolledTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO: Check Radius is in cm
		
		if (!AICOntrolledTank->TankAimingComponent) 
		{
			//UE_LOG(LogTemp, Warning, TEXT("Saith_ATankAIController"));
			return;
		}

		AICOntrolledTank->TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
		//AICOntrolledTank->Fire();
	}
}