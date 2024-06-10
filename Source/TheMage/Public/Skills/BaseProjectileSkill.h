// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Skills/BaseSkill.h"
#include "BaseProjectileSkill.generated.h"

USTRUCT(BlueprintType)
struct FProjectileInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 Damage = 1;

	UPROPERTY(EditAnywhere)
	float KnockbackTime = 0.3f;

	UPROPERTY(EditAnywhere)
	float HorizontalKnockbackPower = 300.f;

	UPROPERTY(EditAnywhere)
	float VerticalKnockbackPower = 100.f;
};


/**
 * 
 */
UCLASS()
class THEMAGE_API ABaseProjectileSkill : public ABaseSkill
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FProjectileInfo ProjectileInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bShouldDestroyedOnTargetOverlapped = true;

protected:
	virtual void OnTargetBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	ABaseProjectileSkill();

	virtual void Init(ABaseCharacter* InOwner, float InLifeSpan);

public:
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
};
