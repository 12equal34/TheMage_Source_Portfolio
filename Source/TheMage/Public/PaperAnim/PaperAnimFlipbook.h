#pragma once
#include "CoreMinimal.h"
#include "PaperAnimFlipbook.generated.h"

class UPaperFlipbook;
class UPaperAnimFrameEffect;

USTRUCT(BlueprintType)
struct FPaperAnimFrameEffectInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int32 StartEffectKeyFrame = 0;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaperAnimFrameEffect> FrameEffectClass;
};


USTRUCT(BlueprintType)
struct FPaperAnimFlipbook
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbook* PF;

	UPROPERTY(EditDefaultsOnly)
	TArray<FPaperAnimFrameEffectInfo> FrameEffectInfos;

	UPROPERTY(EditDefaultsOnly)
	bool bLooping = true;
};
