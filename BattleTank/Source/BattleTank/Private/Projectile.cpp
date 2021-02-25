// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "TankProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("Saith_AProjectile Created"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Projectile Triggered"));
	ProjectileMovement = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement"));
	if (ProjectileMovement)
	{
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovement->Activate();
	}
	
}

