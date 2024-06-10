#include "Monster/Behavior/MonsterBehavior.h"
#include "Monster/MonsterCharacter.h"

void UMonsterBehavior::Init(AMonsterCharacter* InMonsterOwner)
{
	MonsterOwner = InMonsterOwner;
}

void UMonsterBehavior::SetTargetActor(AActor* InTargetActor)
{
	TargetActor = InTargetActor;
}
