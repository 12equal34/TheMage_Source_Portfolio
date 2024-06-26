// This game is making by Gyeong-rok Min.

#include "Components/HPComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHP, Display, All);

UHPComponent::UHPComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;

	checkf(MaxHP > 0.f, TEXT("The maximum HP should be always positive."));
}

void UHPComponent::InitializeComponent()
{
	Super::InitializeComponent();

	checkf(MaxHP > 0.f, TEXT("Setting: The maximum HP should set a positive number."));
	HealFully();
}

void UHPComponent::SetMaxHP(float InMaxHP, AActor* Instigator)
{
	if (MaxHP == InMaxHP)
	{
		return;
	}
	checkf(InMaxHP > 0.f, TEXT("You can't set the maximum HP by a nonpositive number."));

	MaxHP = InMaxHP;
	UE_LOG(LogHP, Display, TEXT("Set Maximum HP: %f (%s)"), MaxHP, *GetOwner()->GetName());
	OnHPBecomeZero.Broadcast(Instigator, HP, MaxHP);
}

void UHPComponent::SetHP(float InHP, AActor* Instigator, bool bCanExcessMax)
{
	checkf(InHP >= 0.f, TEXT("You can't set the current HP by a negative number."));
	if (HP == InHP)
	{
		return;
	}

	HP = InHP;
	if (!bCanExcessMax)
	{
		HP = FMath::Min(HP, MaxHP);
	}

	OnHPChange.Broadcast(Instigator, HP, MaxHP);
	if (IsZero())
	{
		OnHPBecomeZero.Broadcast(Instigator, HP, MaxHP);
	}

	UE_LOG(LogHP, Display, TEXT("Set HP: %f (%f)(%s)"), HP, MaxHP, *GetOwner()->GetName());
}

float UHPComponent::Injure(float InDamage, AActor* Instigator)
{
	checkf(InDamage >= 0.f, TEXT("Received damage is innegative."));
	if (HP == 0.f || InDamage == 0.f)
	{
		return HP;
	}

	HP = FMath::Clamp(HP - InDamage, 0.f, MaxHP);

	OnHPChange.Broadcast(Instigator, HP, MaxHP);
	if (IsZero())
	{
		OnHPBecomeZero.Broadcast(Instigator, HP, MaxHP);
	}

	UE_LOG(LogHP, Display, TEXT("HP: %f (Injured)(%s)"), HP, *GetOwner()->GetName());

	return HP;
}

float UHPComponent::Heal(float InHealth, AActor* Instigator, bool bCanExcessMax)
{
	checkf(InHealth >= 0.f, TEXT("Received health is innegative."));
	if (InHealth == 0.f)
	{
		return HP;
	}

	const float OldHP = HP;
	HP += InHealth;

	if (!bCanExcessMax)
	{
		HP = FMath::Min(HP, MaxHP);
	}

	if (HP != OldHP)
	{
		OnHPChange.Broadcast(Instigator, HP, MaxHP);
	}

	UE_LOG(LogHP, Display, TEXT("HP: %f (Healed)(%s)"), HP, *GetOwner()->GetName());

	return HP;
}

float UHPComponent::HealRatio(float InRatio, AActor* Instigator, bool bCanExcessMax)
{
	check(InRatio >= 0.f && InRatio <= 1.f);
	const float Health = MaxHP * InRatio;

	UE_LOG(LogHP, Display, TEXT("HP: %f (Healed)(%s)"), HP, *GetOwner()->GetName());

	return Heal(Health, Instigator, bCanExcessMax);
}

void UHPComponent::HealFully(AActor* Instigator)
{
	if (HP == MaxHP)
	{
		return;
	}

	HP = MaxHP;

	OnHPChange.Broadcast(Instigator, HP, MaxHP);

	UE_LOG(LogHP, Display, TEXT("HP: %f (Full Healed)(%s)"), HP, *GetOwner()->GetName());
}

bool UHPComponent::IsZero() const
{
	return HP == 0.f;
}

bool UHPComponent::IsLeft() const
{
	return HP > 0.f;
}

bool UHPComponent::IsExcess() const
{
	return HP > MaxHP;
}

bool UHPComponent::IsFull() const
{
	return HP == MaxHP;
}

void UHPComponent::BeginPlay()
{
	Super::BeginPlay();

}