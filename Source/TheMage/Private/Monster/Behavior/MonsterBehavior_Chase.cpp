// By Gyeong-rok Min


#include "Monster/Behavior/MonsterBehavior_Chase.h"
#include "Monster/MonsterCharacter.h"

void UMonsterBehavior_Chase::Init(AMonsterCharacter* InMonsterOwner)
{
	Super::Init(InMonsterOwner);
}

void UMonsterBehavior_Chase::Tick(float DeltaSeconds)
{
	if (!MonsterOwner.IsValid())
	{
		return;
	}

	if (GetTargetActor())
	{
		MonsterOwner->MoveTo(GetTargetActor());
	}
}
