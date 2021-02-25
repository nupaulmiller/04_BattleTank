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
class UTankMovementComponent;

#pragma endregion

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;


	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

#pragma region Private Blueprint Callable
	UFUNCTION(BlueprintCallable, Category = "ErrorHandling")
	void PrintErrorMessage(FString Message);

#pragma endregion

#pragma region Overloaded Method
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
};