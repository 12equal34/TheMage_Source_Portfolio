
#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePlayerCharacter.h"
#include "Mage.generated.h"

UENUM(BlueprintType)
enum class EAuraType : uint8
{
	EAT_None,
	EAT_Normal,
	EAT_Defense,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAuraChangedDelegate);


UCLASS()
class THEMAGE_API AMage : public ABasePlayerCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite)
	TArray<EAuraType> Auras;

	UPROPERTY(BlueprintAssignable)
	FOnAuraChangedDelegate OnAuraChanged;

public:
	AMage();

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~ End AActor Interface.

	virtual void ReceiveDamage(int32 Damage, ABaseCharacter* Damager);

	UFUNCTION(BlueprintCallable)
	void AddAura(EAuraType InAuraType);

	UFUNCTION(BlueprintCallable)
	void PopAura();

	UFUNCTION(BlueprintCallable)
	void PopAuras(int32 Num = 1);

	void SetAuras(const TArray<EAuraType>& NewAuras);

	FORCEINLINE TArray<EAuraType>& GetAuras() { return Auras; }
};
