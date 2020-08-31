// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitComponent, float LaunchSpeed)
{
	if (!Barrel) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Barrel is not Found"));
		return; 
	}
	
	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FCollisionResponseParams ResponseParam;
	TArray<AActor*> ActorsToIgnore;

	OutLaunchVelocity.Size();

	//Calculate out Launch Velocity
	auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this->GetWorld(),
		OUT OutLaunchVelocity,
		StartLocation,
		HitComponent,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		ResponseParam,
		ActorsToIgnore,
		true
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		//UE_LOG(LogTemp, Warning, TEXT("At Launch Speed %f Tank %s is Aiming at: %s from %s"), 
		//LaunchSpeed, *OurTankName, *HitComponent.ToString(), *BarrelLocation.ToString());
		
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		//Move Barrel
		
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find the Projectile Velocity"));
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(5);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}