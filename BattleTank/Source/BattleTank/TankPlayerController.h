// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <UObject/ObjectMacros.h>
#include "TankPlayerController.generated.h"



UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
#pragma region Overridden Functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma endregion
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.333333f;
	
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;
	void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;

};
