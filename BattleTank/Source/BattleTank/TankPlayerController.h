// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

private:
	
#pragma region Overridden Functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region Blueprint Editable Fields
	UPROPERTY(EditAnywhere, Category="NupaulPosition")
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, Category = "NupaulPosition")
	float CrossHairYLocation = 0.333333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.00f;
#pragma endregion

	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;
	void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;
	bool GetLookVectorHitLocation(OUT FVector &HitLocation, FVector LookDirection) const;
};
