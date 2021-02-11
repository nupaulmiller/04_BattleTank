// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTorret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO: Should this tick??
	UE_LOG(LogTemp, Warning, TEXT("Saith_AimingConstructor"));
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitComponent)
{

	UE_LOG(LogTemp, Warning, TEXT("Saith_6"));

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
		false
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Solution Found"), Time);
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTorret* TorrentToSet)
{
	Barrel = BarrelToSet;
	Torret = TorrentToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Torret) return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto TorretRotator = Torret->GetForwardVector().Rotation();

	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	Torret->Rotate(BarrelDeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
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