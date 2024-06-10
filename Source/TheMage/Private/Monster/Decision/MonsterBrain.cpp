#include "Monster/Decision/MonsterBrain.h"
#include "Monster/MonsterCharacter.h"
#include "Monster/Behavior/MonsterBehavior.h"
#include "Monster/Behavior/MonsterBehaviorState.h"
#include "Monster/MonsterHelpers.h"

void UMonsterBrain::Init(AMonsterCharacter* InMonsterOwner)
{
	check(InMonsterOwner);
	MonsterOwner = InMonsterOwner;
	CreateBehaviorMap(MonsterBehaviorClassMap);
}

void UMonsterBrain::Tick(float DeltaSeconds)
{
	ClosestActor = UE::MonsterHelpers::FindClosestActor(MonsterOwner->GetActorLocation(), ActorsInSight);

	if (ClosestActor)
	{
		if (HasToAttack(ClosestActor))
		{
			SetBehavior(EMonsterBehaviorState::Attack);
		}
		else
		{
			SetBehavior(EMonsterBehaviorState::Chase);
		}
	}
	else
	{
		if (bPerceivedUnderAttack)
		{
			SetBehavior(EMonsterBehaviorState::Alert);
		}
		else
		{
			SetBehavior(EMonsterBehaviorState::Wander);
		}
	}

	if (CurrentBehavior)
	{
		CurrentBehavior->SetTargetActor(ClosestActor);
		CurrentBehavior->Tick(DeltaSeconds);
	}
}

void UMonsterBrain::SetBehavior(EMonsterBehaviorState InBehaviorState)
{
	if (CurrentBehaviorState != InBehaviorState)
	{
		CurrentBehaviorState = InBehaviorState;
		if (BehaviorMap.Contains(CurrentBehaviorState))
		{
			CurrentBehavior = BehaviorMap[CurrentBehaviorState];
		}
		else
		{
			CurrentBehavior = nullptr;
		}
	}
}

void UMonsterBrain::CreateBehaviorMap(TMap<EMonsterBehaviorState,TSubclassOf<UMonsterBehavior>>& InMonsterBehaviorClassMap)
{
	BehaviorMap.Empty();
	for (auto&& [State,BehaviorClass] : InMonsterBehaviorClassMap)
	{
		UMonsterBehavior* Behavior = NewObject<UMonsterBehavior>(this, *BehaviorClass);
		Behavior->Init(MonsterOwner.Get());
		BehaviorMap.Add(State, Behavior);
	}
}

bool UMonsterBrain::HasToAttack(AActor* TargetActor)
{
	return false;
}
