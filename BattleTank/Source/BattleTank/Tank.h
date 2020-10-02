#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Always at the bottom

#pragma region Forward Declaration
class UTankAimingComponent;
class UTankBarrel;
class UTankTorret;
class AProjectile;
class UTankTrack;
#pragma endregion


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

#pragma region Public Blueprint Callable
	UFUNCTION(BlueprintCallable)
    void Fire();
#pragma endregion

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

#pragma region Private Blueprint Callable
	UFUNCTION(BlueprintCallable)
		void SetTrackReferences(UTankTrack * LTrack, UTankTrack* RTrack);

	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void SetTorretReference(UTankTorret* TorretToSet);

	UFUNCTION(BlueprintCallable, Category = "ErrorHandling")
	void PrintErrorMessage(FString Message);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 1000; //Find sensible Default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBluePrint; 	//UClass * ProjectileBluePrint;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 5;
#pragma endregion

	//Local Barrel Reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	//Local Track References for movement
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	float LastFireTime = 0;

#pragma region Overloaded Method
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
};