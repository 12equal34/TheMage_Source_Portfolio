#include "Monster/Behavior/MonsterBehavior_Alert.h"
#include "Monster/MonsterCharacter.h"


void UMonsterBehavior_Alert::Tick(float DeltaSeconds)
{
	MonsterOwner->Turn(DeltaSeconds * TurnRate);
}
