#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallClimbingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterClimbWallDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterFallOffWallDelegate);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class UWallClimbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void TryClimbWall(const FVector& MoveInput);

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsClimbingWall() const { return bClimbingWall; }

	UFUNCTION(BlueprintPure)
	bool CanClimbWall() const;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterClimbWallDelegate OnCharacterClimbWall;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterFallOffWallDelegate OnCharacterFallOffWall;

protected:
	UPROPERTY(Transient)
	TObjectPtr<class ACharacter> TargetCharacter;

	UPROPERTY(Transient, VisibleInstanceOnly)
	bool bClimbingWall;

	UPROPERTY(EditDefaultsOnly)
	float MinVelocityToClimbWall = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxVelocityToClimbWall = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float TraceLengthToClimbWall = 40.f;

	UPROPERTY(EditDefaultsOnly)
	float CapsuleRadiusInClimbingWall = 28.f;

	UPROPERTY(Transient)
	float CapsuleRadiusOnBeginPlay;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bDrawDebugTraceTryingClimbWall;
#endif

public:
	UWallClimbingComponent();

	//~ Begin UActorComponent Interface.
	virtual void InitializeComponent() override;
	virtual void BeginPlay();
	//~ End UActorComponent Interface.
	
private:
	void Init(ACharacter* InTargetCharacter);
	void TransferNotClimbingWallState();
	void TransferClimbingWallState();
};

