// By Gyeong-rok Min


#include "Monster/Behavior/MonsterBehavior_Attack.h"
#include "Monster/MonsterCharacter.h"

void UMonsterBehavior_Attack::Init(AMonsterCharacter* InMonsterOwner)
{
	Super::Init(InMonsterOwner);

}

void UMonsterBehavior_Attack::Tick(float DeltaSeconds)
{
	if (!MonsterOwner.IsValid())
	{
		return;
	}

	Timer += DeltaSeconds;

	if (Timer > Delay)
	{
		Timer -= Delay;

		// todo:
	}
}
