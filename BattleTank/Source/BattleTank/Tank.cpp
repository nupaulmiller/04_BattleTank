// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
	//UE_LOG(LogTemp, Error, TEXT("Saith_TankConstruction"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Saith_5"));
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATank::PrintErrorMessage(FString Message)
{
	UE_LOG(LogTemp, Error, TEXT("Error occured: %s"), *Message);
}
