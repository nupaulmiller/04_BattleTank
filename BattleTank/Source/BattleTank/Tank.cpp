// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetTrackReferences(UTankTrack* LTrack, UTankTrack* RTrack)
{
	LeftTrack = LTrack;
	RightTrack = RTrack;
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTorretReference(UTankTorret* TorretToSet)
{
	TankAimingComponent->SetTorretReference(TorretToSet);
}

void ATank::PrintErrorMessage(FString Message)
{
	UE_LOG(LogTemp, Error, TEXT("Error occured: %s"), *Message);
}

void ATank::Fire()
{
	//auto systemTime = FPlatformTime::Seconds();
	bool isReloaded = (LastFireTime == 0 || (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds);
	
	if (Barrel && isReloaded)
	{ 
		//Spawn Projectile At the socket location
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, StartLocation, StartRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("Fire!!!"));
	}
}
