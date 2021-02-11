// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for Aiming State
UENUM()
enum class EFiringStatus : uint8 {Locked, Aiming, Reloading};

class UTankBarrel;
class UTankTorret;
class AProjectile;

//Holds Barrel's properties and Elevates Barrel
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitComponent);

#pragma region Public Blueprint Callable
	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrel* BarrelToSet, UTankTorret* TorrentToSet);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint; 	//UClass * ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 1000; //Find sensible Default

	UFUNCTION(BlueprintCallable)
	void Fire();
#pragma endregion

protected:
	float LastFireTime = 0;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
		override;
	
private:
	UTankBarrel* Barrel = nullptr;
	UTankTorret* Torret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
};
