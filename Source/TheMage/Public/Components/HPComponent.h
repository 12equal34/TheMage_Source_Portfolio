// This game is making by Gyeong-rok Min.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHPChangeDelegate, AActor*, Instigator, float, HP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHPBecomeZeroDelegate, AActor*, Instigator, float, HP, float, MaxHP);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class THEMAGE_API UHPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHPComponent();

	virtual void InitializeComponent() override;

	UFUNCTION(Category="Combat|HPComponent",BlueprintCallable)
	void SetMaxHP(float InMaxHP, AActor* Instigator = nullptr);

	UFUNCTION(Category="Combat|HPComponent",BlueprintCallable)
	void SetHP(float InHP, AActor* Instigator = nullptr, bool bCanExcessMax = false);

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	FORCEINLINE float GetMaxHP() const { return MaxHP; }

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	FORCEINLINE float GetHP() const { return HP; }

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	FORCEINLINE float GetRatioHP() const { return HP / MaxHP; }

	/** returns the HP after damaged. */
	UFUNCTION(Category="Combat|HPComponent", BlueprintCallable)
	float Injure(float InDamage, AActor* Instigator = nullptr);

	/** returns the HP after healed. */
	UFUNCTION(Category="Combat|HPComponent", BlueprintCallable)
	float Heal(float InHealth, AActor* Instigator = nullptr, bool bCanExcessMax = false);

	/** returns the HP after healed. */
	UFUNCTION(Category="Combat|HPComponent", BlueprintCallable)
	float HealRatio(float InRatio, AActor* Instigator = nullptr, bool bCanExcessMax = false);

	UFUNCTION(Category="Combat|HPComponent", BlueprintCallable)
	void HealFully(AActor* Instigator = nullptr);

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	bool IsZero() const;

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	bool IsLeft() const;

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	bool IsExcess() const;

	UFUNCTION(Category="Combat|HPComponent",BlueprintPure)
	bool IsFull() const;

	UPROPERTY(Category="Combat|HPComponent",BlueprintAssignable)
	FHPBecomeZeroDelegate OnHPBecomeZero;

	UPROPERTY(Category="Combat|HPComponent",BlueprintAssignable)
	FHPChangeDelegate OnHPChange;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category="Combat|HPComponent",EditDefaultsOnly,meta=(ClampMin="0"))
	float MaxHP = 5.f;

	UPROPERTY(Category="Combat|HPComponent",Transient,VisibleInstanceOnly)
	float HP;
};
