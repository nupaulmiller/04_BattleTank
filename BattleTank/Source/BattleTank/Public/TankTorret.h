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
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 20;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxRotationDegrees = 90;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinRotationDegrees = -90;
};
