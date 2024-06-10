#pragma once 

#include "CoreMinimal.h"
#include "PaperAnim/PaperAnimCharacter.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReceiveDamageDelegate);

UCLASS()
class THEMAGE_API ABaseCharacter : public APaperAnimCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<class UPositionGuideComponent> PositionGuide;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> Connector;

public:
	ABaseCharacter();

	//~ Begin AActor Interface.
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~ End AActor Interface.

	//~ Begin APaperAnimCharacter Interface.
	virtual void OverrideAnimation(FName AnimName) override;
	//~ End APaperAnimCharacter Interface.

	FORCEINLINE TArray<AActor*>& GetConnectedActors() { return ConnectedActors; }
	FORCEINLINE USphereComponent* GetConnector() const { return Connector; }
	FORCEINLINE const FVector& GetMoveInput() const { return MoveInput; }
	FORCEINLINE bool IsDead() const { return bDead; }
	FORCEINLINE bool IsInvincible() const { return bInvincible; }
	FORCEINLINE FOnReceiveDamageDelegate& GetOnReceiveDamage() { return OnReceiveDamage; }
	FORCEINLINE int32 GetMaxHP() const { return MaxHP; }
	FORCEINLINE int32 GetHP() const { return HP; }

protected:
	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	TArray<AActor*> ConnectedActors;

	UFUNCTION()
	virtual void OnConnectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

	UFUNCTION()
	virtual void OnConnectorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}
	
	UFUNCTION()
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

	UFUNCTION()
	virtual void OnSpriteBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	int32 HP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHP = 3;

	UPROPERTY(Transient, BlueprintReadOnly, VisibleInstanceOnly)
	bool bDead;

	UPROPERTY(Transient, BlueprintReadOnly, VisibleInstanceOnly)
	bool bInvincible;

	UPROPERTY(BlueprintAssignable)
	FOnReceiveDamageDelegate OnReceiveDamage;

	FTimerHandle InvincibleTimer;

	UPROPERTY(EditDefaultsOnly)
	float InvincibleDurationByHit = 2.f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> DieSound;

public:
	UFUNCTION(BlueprintCallable)
	void PlayHitSound() const;

	UFUNCTION(BlueprintCallable)
	void PlayDieSound() const;

	UFUNCTION(BlueprintCallable)
	void HealFully();

	UFUNCTION(BlueprintCallable)
	void SetHP(int32 InHP);

	UFUNCTION(BlueprintCallable)
	void SetMaxHP(int32 InMaxHP);

	UFUNCTION(BlueprintCallable)
	virtual void SetInvincible(bool bNewInvincible) {}

	UFUNCTION(BlueprintCallable)
	void MakeInvincible(float Duration);

	UFUNCTION(BlueprintCallable)
	void MakeInvincibleByHit();

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="OnMadeInvincible"))
	void K2_OnMadeInvincible(float Duration);

	UFUNCTION(BlueprintCallable)
	void Knockback(float KnockbackTime, const FVector& Impulse);

	UFUNCTION(BlueprintNativeEvent)
	void OnKnockbacked(float KnockbackTime);
	virtual void OnKnockbacked_Implementation(float KnockbackTime);

	virtual void ReceiveDamage(int32 Damage, ABaseCharacter* Damager) {}

	virtual bool CanReceiveDamage() const;

	virtual void Die(ABaseCharacter* Damager);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDie"))
	void K2_OnDie(ABaseCharacter* Damager);

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly)
	FVector MoveInput;

	UPROPERTY(Transient, BlueprintReadOnly, VisibleInstanceOnly)
	bool bCanMove = true;

	FTimerHandle EnableMoveTimer;
	FTimerHandle RestoreFallingLateralFrictionTimer;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Move(FVector WorldDirection, float ScaleValue = 1.f);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	bool CanMove() const;
	virtual bool CanMove_Implementation() const { return bCanMove; }

	UFUNCTION(BlueprintCallable)
	void MakeCantMove(float Duration);

	UFUNCTION(BlueprintCallable)
	void SetZeroFallingLateralFriction(float Duration);

	void EnableMove();

	void RestoreFallingLateralFriction();

protected:
	UPROPERTY(Transient)
	float InitFallingLateralFriction;

	UPROPERTY(Transient)
	float InitCapsuleRadius;

	UPROPERTY(Transient)
	float InitCapsuleHalfHeight;

private:
	void CacheInitDatas();
	void BindOverlapEvents();
};
