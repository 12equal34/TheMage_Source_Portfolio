// By Gyeong-rok Min


#include "Monster/Behavior/MonsterBehavior_Wander.h"
#include "Monster/MonsterCharacter.h"

bool FWanderInfo::ShouldMove(float Timer) const
{
	return RestTime < Timer;
}

bool FWanderInfo::ShouldTurn(float Timer) const
{
	return TurnTime < Timer;
}

bool FWanderInfo::ShouldRest(float Timer) const
{
	return MoveTime < Timer;
}

float FWanderInfo::GetTurnYaw() const
{
	return FMath::RandRange(MinTurnYaw, MaxTurnYaw);
}

void FWanderInfo::UpdateMoveTime()
{
	MoveTime = FMath::RandRange(MinMoveTime, MaxMoveTime);
}

void FWanderInfo::UpdateTurnTime()
{
	TurnTime = FMath::RandRange(MinTurnTime, MaxTurnTime);
}

void FWanderInfo::UpdateRestTime()
{
	RestTime = FMath::RandRange(MinRestTime, MaxRestTime);
}

void FWanderInfo::Reset()
{
	TurnTimer = 0.f;
	UpdateMoveTime();
	UpdateTurnTime();
	UpdateRestTime();
}



void UMonsterBehavior_Wander::Tick(float DeltaSeconds)
{
	if (!MonsterOwner.IsValid())
	{
		return;
	}

	StateDuration += DeltaSeconds;

	switch (State)
	{
	case EWanderState::EWS_ForwardMove:
		WanderInfo.TurnTimer += DeltaSeconds;

		if (WanderInfo.ShouldRest(StateDuration))
		{
			StateDuration = 0.f;
			State = EWanderState::EWS_Rest;
			WanderInfo.UpdateRestTime();
		}
		else if (WanderInfo.ShouldTurn(WanderInfo.TurnTimer))
		{
			WanderInfo.TurnTimer = 0.f;
			State = EWanderState::EWS_InstantTurn;
			WanderInfo.UpdateTurnTime();
		}
		break;

	case EWanderState::EWS_InstantTurn:
		State = EWanderState::EWS_ForwardMove;
		break;

	case EWanderState::EWS_Rest:
		if (WanderInfo.ShouldMove(StateDuration))
		{
			StateDuration = 0.f;
			State = EWanderState::EWS_ForwardMove;
			WanderInfo.UpdateMoveTime();
		}
		break;

	default:
		break;
	}

	switch (State)
	{
	case EWanderState::EWS_ForwardMove:
		MonsterOwner->Move(MonsterOwner->GetActorForwardVector());
		break;

	case EWanderState::EWS_InstantTurn:
		MonsterOwner->Turn(WanderInfo.GetTurnYaw());
		break;

	case EWanderState::EWS_Rest:
		break;

	default:
		break;
	}
}

void UMonsterBehavior_Wander::Init(AMonsterCharacter* InMonsterOwner)
{
	Super::Init(InMonsterOwner);
	WanderInfo.Reset();
	StateDuration = 0.f;
	State = EWanderState::EWS_ForwardMove;
}
