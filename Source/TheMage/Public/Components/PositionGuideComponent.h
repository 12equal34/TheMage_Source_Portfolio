#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PositionGuideComponent.generated.h"

class UCapsuleComponent;

USTRUCT(BlueprintType)
struct FLineTraceToCapsuleBottomInfo
{
	GENERATED_BODY()

public:
	FLineTraceToCapsuleBottomInfo()
		:ObjectTypes({UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic)})
	{}

	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	FVector ReachedPosition;

	UPROPERTY(Transient,VisibleInstanceOnly,BlueprintReadOnly)
	float AirHeight;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxTraceReach = 500.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bDrawDebugTraceForOneFrame = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor TraceColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor TraceHitColor = FLinearColor::Green;

	bool LineTraceToCapsuleBottom(const UCapsuleComponent* InCapsuleComponent);
};

UCLASS()
class UPositionGuideComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> TargetCapsule;

	UPROPERTY(BlueprintReadOnly)
	FLineTraceToCapsuleBottomInfo LineTraceToCapsuleBottomInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PositionOffset = FVector(0.f, 0.f, 0.5f);

	void UpdatePositionGuide();
	bool LineTraceToCapsuleBottom();

public:
	UPositionGuideComponent();

	UFUNCTION(BlueprintCallable)
	void SetTargetCapsule(UCapsuleComponent* InTargetCapsule);

	UFUNCTION(BlueprintCallable)
	void StartUpdatePositionGuide();

	UFUNCTION(BlueprintCallable)
	void StopUpdatePositionGuide();

	UFUNCTION(BlueprintCallable)
	float CalculateAirHeight();

	//~ Begin UActorComponent Interface.
	virtual void TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	//~ End UActorComponent Interface.
};

