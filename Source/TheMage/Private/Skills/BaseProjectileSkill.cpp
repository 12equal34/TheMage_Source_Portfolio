// By Gyeong-rok Min


#include "Skills/BaseProjectileSkill.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/BaseCharacter.h"

ABaseProjectileSkill::ABaseProjectileSkill()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->InitialSpeed = 600.f;

}

void ABaseProjectileSkill::Init(ABaseCharacter* InOwner,float InLifeSpan)
{
	Super::Init(InOwner, InLifeSpan);
}


void ABaseProjectileSkill::OnTargetBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABaseCharacter* BaseChar = Cast<ABaseCharacter>(OtherActor);
	if (BaseChar && BaseChar->CanReceiveDamage())
	{
		const FVector ToBaseChar = (BaseChar->GetActorLocation() - GetActorLocation()).GetUnsafeNormal2D();
		const FVector Impulse  = ToBaseChar * ProjectileInfo.HorizontalKnockbackPower + FVector::UpVector * ProjectileInfo.VerticalKnockbackPower;
		BaseChar->Knockback(ProjectileInfo.KnockbackTime, Impulse);
		BaseChar->ReceiveDamage(ProjectileInfo.Damage, OwningCharacter);

		if (bShouldDestroyedOnTargetOverlapped)
		{
			Destroy();
		}
	}
}

