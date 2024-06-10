#pragma once
#include "CoreMinimal.h"
#include "PaperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperAnimFrameEffect_SpawnSkill.generated.h"

enum class ESkillTargetTag : uint8;

UCLASS()
class THEMAGE_API UPaperAnimFrameEffect_SpawnSkill : public UPaperAnimFrameEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ABaseSkill> SkillClass;

	UPROPERTY(EditDefaultsOnly)
	float SkillLifeSpan = 3.f;

	UPROPERTY(EditDefaultsOnly)
	ESkillTargetTag SkillTargetTag;

public:
	virtual void Play_Implementation() override;

	UFUNCTION(BlueprintCallable)
	ABaseSkill* SpawnSkill(const FTransform& Transform);
};

