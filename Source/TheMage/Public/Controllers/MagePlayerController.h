// This game is making by Gyeong-rok Min.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/CameraRestrictorInterface.h"
#include "MagePlayerController.generated.h"

class ACameraRestrictor;

UCLASS()
class THEMAGE_API AMagePlayerController : public APlayerController, public ICameraRestrictorInterface
{
	GENERATED_BODY()

public:
	AMagePlayerController();

protected:
	/** a cached pointer to a player controller */
	UPROPERTY(Transient, Category="MagePlayerController", BlueprintReadOnly)
	TObjectPtr<class ABasePlayerCharacter> ControlledCharacter;

	/** a cached pointer to a player controller */
	UPROPERTY(Transient, Category="MagePlayerController", BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> ControlledCharCameraArm;

	UPROPERTY(Transient, Category="MagePlayerController", BlueprintReadOnly)
	TObjectPtr<ACameraRestrictor> OverlappingCameraRestrictor;

public:
	void SpawnCamera(const FTransform& SpawnTransform, float InLifeSpan);
	void FadeOutCamera();
	void FadeInCamera();

	//~ Begin ICameraRestrictorInterface Interface.
	virtual void SetOverlappingCameraRestrictor_Implementation(ACameraRestrictor* InCameraRestrictor) override;
	virtual ACameraRestrictor* GetOverlappingCameraRestrictor_Implementation() const override;
	//~ End ICameraRestrictorInterface Interface.

	UFUNCTION(BlueprintCallable,Category="Player Camera")
	void UpdateCameraPosition(float DeltaTime);

public:
	//~ Begin AController Interface.
	virtual void SetPawn(APawn* InPawn) override;
	//~ End AController Interface.

protected:
	//~ Begin AController Interface.
	virtual void OnPossess(APawn* InPawn) override;
	//~ End AController Interface.

private:
	UPROPERTY(Category="Camera|FadeInOut",EditAnywhere)
	FLinearColor CameraFadeColor = FLinearColor::Black;

	UPROPERTY(Category="Camera|FadeInOut",EditAnywhere)
	float FadeOutDuration = 1.f;

	UPROPERTY(Category="Camera|FadeInOut",EditAnywhere)
	float FadeInDuration = 1.f;

	UPROPERTY(Category="Camera",EditAnywhere)
	FVector CameraOffset = FVector(0.f, 0.f, 0.f);

	/** If a speed <= 0.f, then immediately move to the target pos. */
	UPROPERTY(Category="Camera",EditAnywhere)
	float CameraInterpSpeed = 5.f;
};
