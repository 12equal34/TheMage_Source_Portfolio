#pragma once 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraRestrictor.generated.h"

UCLASS()
class THEMAGE_API ACameraRestrictor : public AActor
{
	GENERATED_BODY()

public:	
	ACameraRestrictor();

	UFUNCTION(BlueprintPure)
	FVector GetCamreaPosition() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> CameraPosition;

	UPROPERTY(Transient)
	TScriptInterface<class ICameraRestrictorInterface> CameraRestrictedInterface;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBillboardComponent> BillboardComponent;
#endif // WITH_EDITORONLY_DATA
};

