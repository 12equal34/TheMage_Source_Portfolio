#pragma once
#include "CoreMinimal.h"
#include "InventorySaveDatas.generated.h"

USTRUCT()
struct FInventorySaveDatas
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Money;
};
