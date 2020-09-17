// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankControllerBase.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController, public TankControllerBase
{
	GENERATED_BODY()

public:
	ATankAIController();

private:
	virtual void Tick(float DeltaTime) override;
};
