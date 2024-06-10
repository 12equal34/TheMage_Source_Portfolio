#include "Monster/Perception/MonsterSkin.h"
#include "Monster/MonsterCharacter.h"

UMonsterSkin::UMonsterSkin()
{
}

void UMonsterSkin::Init(AMonsterCharacter* InMonsterOwner)
{
	check(InMonsterOwner);
	MonsterOwner = InMonsterOwner;
}

void UMonsterSkin::OnSkinTouchTo(AActor* OtherActor)
{
	ABaseCharacter* PlayerChar = Cast<ABaseCharacter>(OtherActor);
	if (PlayerChar && PlayerChar->CanReceiveDamage())
	{
		const FVector ToPlayer = (PlayerChar->GetActorLocation() - MonsterOwner->GetActorLocation()).GetUnsafeNormal2D();
		const FVector Impulse  = ToPlayer * HorizontalTouchKnockbackPower + FVector::UpVector * VerticalTouchKnockbackPower;
		PlayerChar->Knockback(TouchKnockbackTime, Impulse);
		PlayerChar->ReceiveDamage(TouchDamage, MonsterOwner.Get());
	}
}

void UMonsterSkin::OnHit(AActor* OtherActor)
{
	bPainful = true;

	FTimerDelegate ErasePainDelegate;
	ErasePainDelegate.BindUObject(this, &UMonsterSkin::SetPainful, false);
	MonsterOwner->GetWorldTimerManager().SetTimer(PainTimer, ErasePainDelegate, PainfulDuration, false);
}

void UMonsterSkin::SetPainful(bool bInPainful)
{
	bPainful = bInPainful;
}
