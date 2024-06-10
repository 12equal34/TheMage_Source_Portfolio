// By Gyeong-rok Min


#include "Skills/BaseSkill.h"
#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Libraries/TheMageLibrary.h"

ABaseSkill::ABaseSkill()
{
	PrimaryActorTick.bCanEverTick = false;

	SkillRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SkillRoot"));
	SetRootComponent(SkillRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp0"));
	BoxComponent->SetupAttachment(SkillRoot);
	UTheMageLibrary::SetNoCollision(BoxComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp0"));
	SphereComponent->SetupAttachment(SkillRoot);
	UTheMageLibrary::SetNoCollision(SphereComponent);
}

void ABaseSkill::Init(ABaseCharacter* InOwner, float InLifeSpan)
{
	OwningCharacter = InOwner;
	SetLifeSpan(InLifeSpan);
}

void ABaseSkill::SetSkillTargetTag(ESkillTargetTag InSkillTargetTag)
{
	SkillTargetTag = InSkillTargetTag;

	const bool bUseOverlapEvents = EnumHasAnyFlags(SkillCollisionType, ESkillCollisionType::ESCT_UseBeginEndOverlap);

	if (bUseOverlapEvents)
	{
		if (EnumHasAllFlags(SkillCollisionType,ESkillCollisionType::ESCT_BoxBeginOverlap))
		{
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseSkill::OnBeginOverlap);
		}
		if (EnumHasAllFlags(SkillCollisionType,ESkillCollisionType::ESCT_BoxEndOverlap))
		{
			BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseSkill::OnEndOverlap);
		}
		if (EnumHasAllFlags(SkillCollisionType,ESkillCollisionType::ESCT_SphereBeginOverlap))
		{
			SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseSkill::OnBeginOverlap);
		}
		if (EnumHasAllFlags(SkillCollisionType,ESkillCollisionType::ESCT_SphereEndOverlap))
		{
			SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseSkill::OnEndOverlap);
		}
	}

	if (EnumHasAnyFlags(SkillCollisionType,ESkillCollisionType::ESCT_Box))
	{
		BoxComponent->SetGenerateOverlapEvents(bUseOverlapEvents);
	}
	else
	{
		BoxComponent->SetGenerateOverlapEvents(false);
	}

	if (EnumHasAnyFlags(SkillCollisionType,ESkillCollisionType::ESCT_Sphere))
	{
		SphereComponent->SetGenerateOverlapEvents(bUseOverlapEvents);
	}
	else
	{
		SphereComponent->SetGenerateOverlapEvents(false);
	}

	if (EnumHasAnyFlags(SkillTargetTag,ESkillTargetTag::ESTT_Player))
	{
		if (EnumHasAnyFlags(SkillCollisionType,ESkillCollisionType::ESCT_Box))
		{
			UTheMageLibrary::SetPlayerBodyDetectorCollision(BoxComponent);
		}
		if (EnumHasAnyFlags(SkillCollisionType,ESkillCollisionType::ESCT_Sphere))
		{
			UTheMageLibrary::SetPlayerBodyDetectorCollision(SphereComponent);
		}
	}

	if (EnumHasAnyFlags(SkillTargetTag,ESkillTargetTag::ESTT_Monster))
	{
		if (EnumHasAnyFlags(SkillCollisionType,ESkillCollisionType::ESCT_Box))
		{
			UTheMageLibrary::SetMonsterBodyDetectorCollision(BoxComponent);
		}
		if (EnumHasAnyFlags(SkillCollisionType,ESkillCollisionType::ESCT_Sphere))
		{
			UTheMageLibrary::SetMonsterBodyDetectorCollision(SphereComponent);
		}
	}
}

bool ABaseSkill::IsSkillTargetActor(AActor* TargetActor) const
{
	return (EnumHasAnyFlags(SkillTargetTag,ESkillTargetTag::ESTT_Player)  && UTheMageLibrary::HasPlayerTag(TargetActor))
		|| (EnumHasAnyFlags(SkillTargetTag,ESkillTargetTag::ESTT_Monster) && UTheMageLibrary::HasMonsterTag(TargetActor));
}

void ABaseSkill::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseSkill::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if ( IsSkillTargetActor(OtherActor) )
	{
		OnTargetBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ABaseSkill::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if ( IsSkillTargetActor(OtherActor) )
	{
		OnTargetEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	}
}
