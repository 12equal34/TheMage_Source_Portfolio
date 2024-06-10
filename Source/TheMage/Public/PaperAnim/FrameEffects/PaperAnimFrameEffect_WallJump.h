#pragma once
#include "CoreMinimal.h"
#include "PaperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperAnimFrameEffect_WallJump.generated.h"

UCLASS()
class UPaperAnimFrameEffect_WallJump : public UPaperAnimFrameEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TWeakObjectPtr<class ABaseCharacter> BaseChar;

	UPROPERTY(EditDefaultsOnly)
	float HorizontalLaunchVelocity = 700.f;

	UPROPERTY(EditDefaultsOnly)
	float VerticalLaunchVelocity = 1400.f;

	UPROPERTY(EditDefaultsOnly)
	float RestoreFallingLateralFrictionTimer = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CantMoveTimer = 0.1f;

public:
	UPaperAnimFrameEffect_WallJump();

	virtual void OnInit(APaperAnimCharacter* InPaperAnimChar);
	virtual void Play_Implementation() override;
};
