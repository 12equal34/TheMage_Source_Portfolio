#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MonsterBrain.generated.h"

class UMonsterBehavior;
enum class EMonsterBehaviorState: uint8;

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class THEMAGE_API UMonsterBrain : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class AMonsterCharacter> MonsterOwner;

	UPROPERTY(Transient, BlueprintReadOnly)
	EMonsterBehaviorState CurrentBehaviorState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<class UMonsterBehavior> CurrentBehavior;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	TMap<EMonsterBehaviorState, UMonsterBehavior*> BehaviorMap;

public:
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<AActor*> ActorsInSight;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bPerceivedUnderAttack;

	UPROPERTY(Transient, BlueprintReadOnly)
	AActor* ClosestActor;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EMonsterBehaviorState, TSubclassOf<UMonsterBehavior>> MonsterBehaviorClassMap;

public:
	virtual void Init(AMonsterCharacter* InMonsterOwner);

	void Tick(float DeltaSeconds);

	void SetBehavior(EMonsterBehaviorState InBehaviorState);

	void CreateBehaviorMap(TMap<EMonsterBehaviorState, TSubclassOf<UMonsterBehavior>>& InMonsterBehaviorClassMap);

	virtual bool HasToAttack(AActor* TargetActor);
};

