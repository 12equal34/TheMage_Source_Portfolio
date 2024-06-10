#pragma once
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperAnimCharacter.generated.h"

UCLASS()
class THEMAGE_API APaperAnimCharacter : public APaperCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UPaperAnimAsset> AnimAsset;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<class UPaperAnimPlayer> AnimPlayer;

private:
	UPROPERTY(Transient, VisibleInstanceOnly)
	FName CurrentAnimName;

	UPROPERTY(Transient)
	bool bIsOverridingAnim;

	UPROPERTY(Transient)
	bool bRightFace;

	UPROPERTY(Transient)
	bool bReverseFace;

public:
	APaperAnimCharacter();

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~ End AActor Interface.

public:
	virtual void UpdateAnimation(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	virtual void OverrideAnimation(FName AnimName);

	UFUNCTION(BlueprintCallable)
	void SetOverridingAnim(bool bInOverridingAnim);

	UFUNCTION(BlueprintNativeEvent)
	FName CalculateAnimation();
	virtual FName CalculateAnimation_Implementation();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsOverridingAnim() const { return bIsOverridingAnim; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsCurrentAnim(FName AnimName) const { return CurrentAnimName == AnimName; }

	FORCEINLINE UPaperAnimPlayer* GetAnimPlayer() const { return AnimPlayer; }

public:
	UFUNCTION(BlueprintCallable)
	void SetReverseFace(bool bInReverseFace);

	UFUNCTION(BlueprintCallable)
	void AdjustSpriteLocationToBottomOfCapsule();

	UFUNCTION(BlueprintCallable)
	void UpdateSpriteRotation();

public:
	UFUNCTION(BlueprintPure)
	FVector GetFaceVector() const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsRightFace() const { return bRightFace; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsReverseFace() const { return bReverseFace; }
};
