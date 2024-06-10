#pragma once
#include "CoreMinimal.h"
#include "LevelSaveDatas.generated.h"

USTRUCT(BlueprintType)
struct FLevelSaveDatas
{
	GENERATED_BODY()

public:
	FLevelSaveDatas();

	UPROPERTY(BlueprintReadOnly)
	FName SaveMapName;
};
