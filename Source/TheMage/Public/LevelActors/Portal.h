// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class THEMAGE_API APortal : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName PortalMapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAutoSaveOnEnter;

	UFUNCTION(BlueprintCallable)
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
	void OnPortalEnter(class AMage* InMage);
	virtual void OnPortalEnter_Implementation(class AMage* InMage);

public:
	APortal();

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	//~ End AActor Interface.


};
