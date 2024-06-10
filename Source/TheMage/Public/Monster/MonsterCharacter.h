// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEMAGE_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UMonsterComponent> MonsterComponent;

protected:
	virtual void OnConnectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSpriteBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnConnectorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void SetInvincible(bool bNewInvincible);

public:
	FORCEINLINE UMonsterComponent* GetMonsterComponent() const { return MonsterComponent; }

public:
	AMonsterCharacter();

	virtual void ReceiveDamage(int32 Damage, ABaseCharacter* Damager);

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~ End AActor Interface.

public:
	void Turn(float DeltaYaw);

	void MoveTo(AActor* TargetActor, float ScaleValue = 1.f, float ToleranceDistSq = UE_KINDA_SMALL_NUMBER);

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="OnTurn"))
	void K2_OnTurn(float OldYaw, float NewYaw);
};
