#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Always at the bottom

#pragma region Forward Declaration
class UTankAimingComponent;
class UTankBarrel;
class UTankTorret;
#pragma endregion

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

#pragma region Blueprint Callable
	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void SetTorretReference(UTankTorret* TorretToSet);

	UFUNCTION(BlueprintCallable, Category = "ErrorHandling")
	void PrintErrorMessage(FString Message);

	UFUNCTION(BlueprintCallable, Category = "ErrorHandling")
	void Fire();

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; //Find sensible Default
#pragma endregion

#pragma region Overloaded Method
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
};