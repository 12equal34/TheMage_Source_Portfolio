#pragma once 
#include "CoreMinimal.h"
#include "PaperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperAnimFrameEffect_RootMotion.generated.h"

class UCurveFloat;
struct FRootMotionSource_ConstantForce;
enum class ERootMotionSourceSettingsFlags : uint8;
enum class ERootMotionFinishVelocityMode : uint8;
enum class ERootMotionAccumulateMode : uint8;

UCLASS()
class THEMAGE_API UPaperAnimFrameEffect_RootMotion : public UPaperAnimFrameEffect
{
	GENERATED_BODY()
	
public:
	virtual void Play_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void ApplyRootMotion(const FVector& Direction, float Power = -1.f, float Duration = -1.f);

private:
	FRootMotionSource_ConstantForce CreateRootMotionSourceInternal() const;

protected:
	TSharedPtr<FRootMotionSource_ConstantForce> RootMotionSourcePtr;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	FName RootMotionInstanceName = FName(TEXT("PaperAnimFrameEffect_RootMotion"));

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	uint16 RootMotionPriority = 5u;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	TObjectPtr<UCurveFloat> RootMotionStrengthOverTime;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	ERootMotionSourceSettingsFlags RootMotionSourceSettingsFlags;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	ERootMotionFinishVelocityMode FinishVelocityMode;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	ERootMotionAccumulateMode AccumulateMode;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion")
	FVector FinishVelocity;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion",meta=(ClampMin="0"))
	float DefaultDuration = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category="RootMotion",meta=(ClampMin="0"))
	float DefaultPower = 1200.f;
};

