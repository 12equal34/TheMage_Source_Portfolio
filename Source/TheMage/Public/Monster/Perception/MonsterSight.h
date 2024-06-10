#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MonsterSight.generated.h"

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class THEMAGE_API UMonsterSight : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class AMonsterCharacter> MonsterOwner;

#if WITH_EDITORONLY_DATA
protected:
	UPROPERTY(EditAnywhere)
	bool bDrawDebug = false;

	UPROPERTY(EditAnywhere)
	FLinearColor DebugSightConeColor = FLinearColor::Blue;

	UPROPERTY(EditAnywhere)
	FLinearColor DebugTraceColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere)
	FLinearColor DebugTraceHitColor = FLinearColor::Red;

public:
	void DrawDebugSightCone(bool bPersistentLines = false, float LifeTime = 0.f);
#endif

public:
	UPROPERTY(EditAnywhere)
	float BackwardOffset = 0.f;

	UPROPERTY(EditAnywhere)
	float NearClippingRadius = 0.f;

	UPROPERTY(EditAnywhere)
	float FarClippingRadius  = 500.f;

	UPROPERTY(EditAnywhere)
	float PeripheralVisionAngle = 90.f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> SightCollisionChannel = ECC_Visibility;

public:
	UMonsterSight();

	virtual void Init(AMonsterCharacter* InMonsterOwner);

	FVector GetSightConeOrigin() const;

	bool IsInSightCone(const FVector& TargetLocation);
	bool IsVisible(AActor* TargetActor);
	bool ComputeVisibility(AActor* TargetActor, bool bTraceComplex = false);
};
