#pragma once
#include "CoreMinimal.h"
#include "PaperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperAnimFrameEffect_DestroyOwner.generated.h"

UCLASS()
class THEMAGE_API UPaperAnimFrameEffect_DestroyOwner : public UPaperAnimFrameEffect
{
	GENERATED_BODY()

public:
	virtual void Play_Implementation() override;

};

