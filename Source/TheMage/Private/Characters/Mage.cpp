
#include "Characters/Mage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetTraceUtils.h"
#include "Components/CapsuleComponent.h"
#include "GameInstances/TheMageGameInstance.h"
//#include "Kismet/GameplayStatics.h"

AMage::AMage()
{
	GetCapsuleComponent()->SetCapsuleRadius(34.f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(80.f);
}

void AMage::BeginPlay()
{
	Super::BeginPlay();

	if (UTheMageGameInstance* TheMageGameInstance = Cast<UTheMageGameInstance>(GetGameInstance()))
	{
		TheMageGameInstance->LoadMageSaveDatas(this);
	}
}

void AMage::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AMage::ReceiveDamage(int32 Damage,ABaseCharacter* Damager)
{
	const int32 OldNumAuras = Auras.Num();

	for (; Damage > 0; Damage--)
	{
		if (!Auras.IsEmpty() && Auras.Last() == EAuraType::EAT_Defense)
		{
			Auras.Pop(EAllowShrinking::No);
		}
		else if (--HP == 0)
		{
			Die(Damager);
			break;
		}
	}

	if (OldNumAuras != Auras.Num())
	{
		OnAuraChanged.Broadcast();
	}

	if (HP > 0)
	{
		FName HitAnimName = GetCharacterMovement()->IsCrouching() ? TEXT("SitHit") : TEXT("Hit");
		OverrideAnimation(HitAnimName);
		MakeInvincibleByHit();
		PlayHitSound();
	}

	OnReceiveDamage.Broadcast();
}

void AMage::AddAura(EAuraType InAuraType)
{
	if (Auras.Num() < HP)
	{
		Auras.Add(InAuraType);
		OnAuraChanged.Broadcast();
	}
}

void AMage::PopAura()
{
	if (Auras.Num() > 0)
	{
		Auras.Pop(EAllowShrinking::No);
		OnAuraChanged.Broadcast();
	}
}

void AMage::PopAuras(int32 Num)
{
	if (Auras.Num() == 0 || Num < 1) return;
	for (int32 i = 0; i < Num; i++)
	{
		Auras.Pop(EAllowShrinking::No);
		if (Auras.Num() == 0) break;
	}
	OnAuraChanged.Broadcast();
}

void AMage::SetAuras(const TArray<EAuraType>& NewAuras)
{
	Auras = NewAuras;
}
