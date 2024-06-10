// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class THEMAGE_API AItem : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UPaperFlipbookComponent> Sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UItemDataAsset> ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class USoundBase> SoundOnBeginPlay;

	UPROPERTY(EditDefaultsOnly)
	FVector VelocityOnBeginPlay = FVector(0.f, 0.f, 450.f);

	UPROPERTY(EditDefaultsOnly)
	float RotateRate = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float FloatingRate = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float FloatingAmplitude = 10.f;

	UPROPERTY(Transient)
	float FloatingTime;

public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
