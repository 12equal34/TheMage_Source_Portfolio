#pragma once
#include "CoreMinimal.h"
#include "MageSaveDatas.generated.h"

enum class EAuraType : uint8;

USTRUCT()
struct FMageSaveDatas
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 MaxHP = 5;

	UPROPERTY()
	int32 HP = 5;

	UPROPERTY()
	TArray<EAuraType> Auras;
};
