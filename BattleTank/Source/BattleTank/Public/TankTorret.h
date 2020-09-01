#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTorret.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTorret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward movement | +1 is max up movement
	void Turn(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxRotationDegrees = 90;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinRotationDegrees = -90;
};
