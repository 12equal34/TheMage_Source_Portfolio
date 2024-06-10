#pragma once 
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MonsterSkin.generated.h"

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class THEMAGE_API UMonsterSkin : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class AMonsterCharacter> MonsterOwner;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	bool bPainful;

	UPROPERTY(EditAnywhere)
	int32 TouchDamage = 1;

	UPROPERTY(EditAnywhere)
	float TouchKnockbackTime = 0.3f;

	UPROPERTY(EditAnywhere)
	float HorizontalTouchKnockbackPower = 500.f;

	UPROPERTY(EditAnywhere)
	float VerticalTouchKnockbackPower = 1000.f;

	UPROPERTY(EditAnywhere)
	float PainfulDuration = 3.f;

	FTimerHandle PainTimer;

public:
	UMonsterSkin();

	virtual void Init(AMonsterCharacter* InMonsterOwner);

	virtual void OnSkinTouchTo(AActor* OtherActor);
	virtual void OnHit(AActor* OtherActor);

	void SetPainful(bool bInPainful);

	FORCEINLINE bool IsPainful() const { return bPainful; }
};

