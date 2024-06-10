#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

UCLASS()
class THEMAGE_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UWallClimbingComponent> WallClimbingComponent;

	virtual void SetInvincible(bool bNewInvincible);

public:
	ABasePlayerCharacter();

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~ End AActor Interface.

	virtual bool CanMove_Implementation() const;
	virtual bool CanCrouch() const;

	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE UWallClimbingComponent* GetWallClimbingComponent() const { return WallClimbingComponent; }

private:
	UPROPERTY(Category="BasePlayerCharacter|Camera",VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(Category="BasePlayerCharacter|Camera",VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComponent;

	UFUNCTION()
	void OnClimbWall();

	UFUNCTION()
	void OnFallOffWall();
};
