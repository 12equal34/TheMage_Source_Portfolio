// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "PaperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperAnimFrameEffect_AddVelocity.generated.h"

UENUM(BlueprintType)
enum class EAddVelocityType : uint8
{
	EAVT_Front,
	EAVT_Back,
	EAVT_Left,
	EAVT_Right,
	EAVT_InputDirection,
};

/**
 * 
 */
UCLASS()
class THEMAGE_API UPaperAnimFrameEffect_AddVelocity : public UPaperAnimFrameEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TWeakObjectPtr<class ABaseCharacter> BaseChar;

	UPROPERTY(EditDefaultsOnly)
	float Speed = 200.f;

	UPROPERTY(EditDefaultsOnly)
	EAddVelocityType AddVelocityType;

public:
	virtual void OnInit(APaperAnimCharacter* InPaperAnimChar);
	virtual void Play_Implementation() override;
};
