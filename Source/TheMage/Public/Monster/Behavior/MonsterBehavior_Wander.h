// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Monster/Behavior/MonsterBehavior.h"
#include "MonsterBehavior_Wander.generated.h"

UENUM(BlueprintType)
enum class EWanderState: uint8
{
	EWS_ForwardMove,
	EWS_InstantTurn,
	EWS_Rest
};


USTRUCT(BlueprintType)
struct FWanderInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,meta=(ClampMin="-180",ClampMax="0"))
	float MinTurnYaw = -150.f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0",ClampMax="180"))
	float MaxTurnYaw = 150.f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0"))
	float MinMoveTime = 2.f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0"))
	float MaxMoveTime = 4.f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0.1"))
	float MinTurnTime = 1.f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0.1"))
	float MaxTurnTime = 2.f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0"))
	float MinRestTime = 0.5f;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0"))
	float MaxRestTime = 2.f;

protected:
	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	float MoveTime;

	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	float TurnTime;

	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	float RestTime;

public:
	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	float TurnTimer;

	bool ShouldMove(float Timer) const;
	bool ShouldTurn(float Timer) const;
	bool ShouldRest(float Timer) const;

	float GetTurnYaw() const;

	void UpdateMoveTime();
	void UpdateTurnTime();
	void UpdateRestTime();

	void Reset();
};


/**
 * 
 */
UCLASS()
class THEMAGE_API UMonsterBehavior_Wander : public UMonsterBehavior
{
	GENERATED_BODY()
	
protected:
	EWanderState State;
	float StateDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWanderInfo WanderInfo;

public:
	virtual void Init(AMonsterCharacter* InMonsterOwner);

	virtual void Tick(float DeltaSeconds) override;
};
