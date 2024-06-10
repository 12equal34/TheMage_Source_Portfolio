#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MonsterBehavior.generated.h"

UCLASS(BlueprintType, Blueprintable)
class THEMAGE_API UMonsterBehavior : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class AMonsterCharacter> MonsterOwner;

	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<AActor> TargetActor;

public:
	virtual void Init(AMonsterCharacter* InMonsterOwner);

	virtual void Tick(float DeltaSeconds) {}

	void SetTargetActor(AActor* InTargetActor);

	FORCEINLINE AActor* GetTargetActor() const { return TargetActor.Get(); }
};

