#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMonsterBehaviorState: uint8
{
	None,
	Wander,
	Alert,
	Chase,
	Attack,
	Flee
};
