// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"


USTRUCT(BlueprintType)
struct FTrapInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 Damage = 1;

	UPROPERTY(EditAnywhere)
	float KnockbackTime = 0.3f;

	UPROPERTY(EditAnywhere)
	float HorizontalKnockbackPower = 700.f;

	UPROPERTY(EditAnywhere)
	float VerticalKnockbackPower = 600.f;
};


UCLASS()
class THEMAGE_API ATrap : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USceneComponent> TrapRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	FTrapInfo TrapInfo;

public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="OnTrapped"))
	void K2_OnTrapped(ABaseCharacter* TrappedChar);
};
