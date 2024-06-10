#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_SpawnSkill.h"
#include "Skills/BaseSkill.h"
#include "Characters/BaseCharacter.h"

void UPaperAnimFrameEffect_SpawnSkill::Play_Implementation()
{

}

ABaseSkill* UPaperAnimFrameEffect_SpawnSkill::SpawnSkill(const FTransform& Transform)
{
	ABaseSkill* Skill = nullptr;
	if (ABaseCharacter* BaseChar = Cast<ABaseCharacter>(PaperAnimChar))
	{
		if (UWorld* World = BaseChar->GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = BaseChar;
			SpawnParams.Instigator = BaseChar;

			Skill = World->SpawnActor<ABaseSkill>(*SkillClass,Transform,SpawnParams);
			Skill->Init(BaseChar,SkillLifeSpan);
			Skill->SetSkillTargetTag(SkillTargetTag);
		}
		
	}

	return Skill;
}