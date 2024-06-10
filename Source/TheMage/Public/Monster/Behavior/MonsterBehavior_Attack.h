// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Monster/Behavior/MonsterBehavior.h"
#include "MonsterBehavior_Attack.generated.h"

/**
 * 
 */
UCLASS()
class THEMAGE_API UMonsterBehavior_Attack : public UMonsterBehavior
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly)
	float Timer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Delay = 3.f;

public:
	virtual void Init(AMonsterCharacter* InMonsterOwner);

	virtual void Tick(float DeltaSeconds);
};
