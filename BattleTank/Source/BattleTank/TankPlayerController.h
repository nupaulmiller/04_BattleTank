#pragma once
#include "TankControllerBase.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController, public TankControllerBase
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
#pragma region Overridden Functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region Blueprint Editable Fields
	UPROPERTY(EditDefaultsOnly, Category="NupaulPosition")
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "NupaulPosition")
	float CrossHairYLocation = 0.333333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.00f;
#pragma endregion
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;
	void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;
	bool GetLookVectorHitLocation(OUT FVector &HitLocation, FVector LookDirection) const;
};