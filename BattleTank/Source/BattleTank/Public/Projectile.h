// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

#pragma region Forward Declaration
class UTankProjectileMovementComponent;
#pragma endregion


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankProjectileMovementComponent *ProjectileMovement = nullptr;
};
