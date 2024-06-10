// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Monster/Behavior/MonsterBehavior.h"
#include "MonsterBehavior_Chase.generated.h"

/**
 * 
 */
UCLASS()
class THEMAGE_API UMonsterBehavior_Chase : public UMonsterBehavior
{
	GENERATED_BODY()

public:
	virtual void Init(AMonsterCharacter* InMonsterOwner);

	virtual void Tick(float DeltaSeconds);
};
