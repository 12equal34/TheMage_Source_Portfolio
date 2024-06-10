#pragma once
#include "CoreMinimal.h"
#include "Monster/Behavior/MonsterBehavior.h"
#include "MonsterBehavior_Alert.generated.h"

UCLASS()
class THEMAGE_API UMonsterBehavior_Alert : public UMonsterBehavior
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float TurnRate = 50.f;

public:
	virtual void Tick(float DeltaSeconds);
};

