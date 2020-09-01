#include "TankTorret.h"

void UTankTorret::Turn(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto HorizontalChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewHorizontal = GetRelativeRotation().Yaw + HorizontalChange;
	auto Horizontal = FMath::Clamp<float>(RawNewHorizontal, MinRotationDegrees , MaxRotationDegrees);

	SetRelativeRotation(FRotator(0, Horizontal, 0));
}