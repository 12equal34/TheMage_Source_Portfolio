#pragma once
#include "CoreMinimal.h"
#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_RootMotion.h"
#include "PaperAnimFrameEffect_Dash.generated.h"

UCLASS()
class THEMAGE_API UPaperAnimFrameEffect_Dash : public UPaperAnimFrameEffect_RootMotion
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TWeakObjectPtr<class ABasePlayerCharacter> PlayerChar;

public:
	UPaperAnimFrameEffect_Dash();

	virtual void OnInit(APaperAnimCharacter* InPaperAnimChar);
	virtual void Play_Implementation() override;
};
