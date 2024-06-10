#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEMAGE_API UMonsterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void TickMonster(float DeltaSeconds);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMonsterBrain> BrainClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMonsterSight> SightClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMonsterSkin> SkinClass;

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<class AMonsterCharacter> MonsterOwner;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UMonsterBrain> Brain;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UMonsterSight> Sight;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UMonsterSkin> Skin;

private:
	void Init(AMonsterCharacter* InMonsterOwner);
	void CreateMonsterBrain();
	void CreateMonsterSight();
	void CreateMonsterSkin();

public:
	FORCEINLINE TSubclassOf<UMonsterBrain> GetMonsterBrainClass() const { return BrainClass; }
	FORCEINLINE TSubclassOf<UMonsterSight> GetMonsterSightClass() const { return SightClass; }
	FORCEINLINE TSubclassOf<UMonsterSkin>  GetMonsterSkinClass()  const { return SkinClass; }

	FORCEINLINE UMonsterBrain* GetMonsterBrain() const { return Brain; }
	FORCEINLINE UMonsterSight* GetMonsterSight() const { return Sight; }
	FORCEINLINE UMonsterSkin*  GetMonsterSkin()  const { return Skin; }

public:
	UMonsterComponent();

	//~ Begin UActorComponent Interface.
	virtual void BeginPlay() override;
	//~ End UActorComponent Interface.


#if WITH_EDITORONLY_DATA
private:
	UPROPERTY(EditAnywhere)
	bool bDrawDebug = false;
#endif
};

