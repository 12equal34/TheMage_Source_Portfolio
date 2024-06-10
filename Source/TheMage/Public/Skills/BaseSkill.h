// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSkill.generated.h"


UENUM(BlueprintType, meta=(Bitflags,UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ESkillCollisionType : uint8
{
	ESCT_None      = 0x00 ,
	ESCT_Box       = 0x01 UMETA(Hidden),
	ESCT_Sphere    = 0x02 UMETA(Hidden),
	ESCT_BoxSphere = ESCT_Box|ESCT_Sphere UMETA(Hidden),

	ESCT_UseBeginOverlap = 0x04 UMETA(Hidden),
	ESCT_UseEndOverlap   = 0x08 UMETA(Hidden),
	ESCT_UseBeginEndOverlap = ESCT_UseBeginOverlap|ESCT_UseEndOverlap UMETA(Hidden),

	ESCT_BoxBeginOverlap    = ESCT_Box|ESCT_UseBeginOverlap,
	ESCT_BoxEndOverlap      = ESCT_Box|ESCT_UseEndOverlap,
	ESCT_BoxBeginEndOverlap = ESCT_Box|ESCT_UseBeginEndOverlap,

	ESCT_SphereBeginOverlap    = ESCT_Sphere|ESCT_UseBeginOverlap,
	ESCT_SphereEndOverlap      = ESCT_Sphere|ESCT_UseEndOverlap,
	ESCT_SphereBeginEndOverlap = ESCT_Sphere|ESCT_UseBeginEndOverlap,
	
	ESCT_BoxSphereBeginOverlap    = ESCT_BoxSphere|ESCT_UseBeginOverlap,
	ESCT_BoxSphereEndOverlap      = ESCT_BoxSphere|ESCT_UseEndOverlap,
	ESCT_BoxSphereBeginEndOverlap = ESCT_BoxSphere|ESCT_UseBeginEndOverlap
};
ENUM_CLASS_FLAGS(ESkillCollisionType);



UENUM(BlueprintType, meta=(Bitflags,UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ESkillTargetTag : uint8
{
	ESTT_None    = 0x00,
	ESTT_Player  = 0x01,
	ESTT_Monster = 0x02,
	ESTT_PlayerAndMonster = 0x03,
};
ENUM_CLASS_FLAGS(ESkillTargetTag);



UCLASS()
class THEMAGE_API ABaseSkill : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<class ABaseCharacter> OwningCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USceneComponent> SkillRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditDefaultsOnly)
	ESkillCollisionType SkillCollisionType;

	UPROPERTY(EditDefaultsOnly)
	ESkillTargetTag SkillTargetTag;

public:	
	ABaseSkill();

	virtual void Init(ABaseCharacter* InOwner, float InLifeSpan);

	void SetSkillTargetTag(ESkillTargetTag InSkillTargetTag);

	bool IsSkillTargetActor(AActor* TargetActor) const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE ABaseCharacter* GetPaperAnimCharacter() const { return OwningCharacter; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UBoxComponent* GetBoxComponent() const { return BoxComponent; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE USphereComponent* GetSphereComponent() const { return SphereComponent; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UNiagaraComponent* GetNiagaraComponent() const { return NiagaraComponent; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnTargetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	virtual void OnTargetBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {}

	UFUNCTION(BlueprintNativeEvent)
	void OnTargetEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void OnTargetEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}
};
