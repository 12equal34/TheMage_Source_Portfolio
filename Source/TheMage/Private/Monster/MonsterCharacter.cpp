// By Gyeong-rok Min

#include "Monster/MonsterCharacter.h"
#include "Monster/MonsterComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Libraries/TheMageLibrary.h"
#include "Monster/Perception/MonsterSkin.h"

AMonsterCharacter::AMonsterCharacter()
{
	Tags.Add(UTheMageLibrary::GetMonsterTag());

	UTheMageLibrary::SetMonsterBodyCollision(GetSprite());
	UTheMageLibrary::SetMonsterPawnCollision(GetCapsuleComponent());
	UTheMageLibrary::SetPlayerPawnDetectorCollision(GetConnector());

	GetSprite()->SetGenerateOverlapEvents(true);

	MonsterComponent = CreateDefaultSubobject<UMonsterComponent>(TEXT("MonsterComponent"));
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsDead())
	{
		MonsterComponent->TickMonster(DeltaSeconds);
	}
}

void AMonsterCharacter::OnConnectorBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (UTheMageLibrary::HasPlayerTag(OtherActor))
	{
		ConnectedActors.Add(OtherActor);
	}
}

void AMonsterCharacter::OnConnectorEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if (UTheMageLibrary::HasPlayerTag(OtherActor))
	{
		ConnectedActors.Remove(OtherActor);
	}
}

void AMonsterCharacter::SetInvincible(bool bNewInvincible)
{
	if (bInvincible != bNewInvincible)
	{
		bInvincible = bNewInvincible;
		if (bInvincible)
		{
			UTheMageLibrary::SetNoCollision(GetSprite());
		}
		else
		{
			UTheMageLibrary::SetMonsterBodyCollision(GetSprite());
		}
	}
}

void AMonsterCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	
}

void AMonsterCharacter::OnSpriteBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (UTheMageLibrary::HasPlayerTag(OtherActor))
	{
		if (!IsDead() && MonsterComponent->GetMonsterSkin())
		{
			MonsterComponent->GetMonsterSkin()->OnSkinTouchTo(OtherActor);
		}
	}
}

void AMonsterCharacter::Turn(float DeltaYaw)
{
	if (CanMove())
	{
		const float OldYaw = GetActorRotation().Yaw;
		const float NewYaw = OldYaw + DeltaYaw;
		SetActorRotation(FRotator(0.f, NewYaw, 0.f));
		K2_OnTurn(OldYaw, NewYaw);
	}
}

void AMonsterCharacter::MoveTo(AActor* TargetActor, float ScaleValue, float ToleranceDistSq)
{
	if (CanMove())
	{
		const FVector ToTarget = TargetActor->GetActorLocation() - GetActorLocation();
		const FVector NormToTarget = ToTarget.GetSafeNormal(ToleranceDistSq, FVector::ZeroVector);
		if (NormToTarget != FVector::ZeroVector)
		{
			Move(NormToTarget, ScaleValue);
		}
	}
}

void AMonsterCharacter::ReceiveDamage(int32 Damage,ABaseCharacter* Damager)
{
	HP = FMath::Clamp(HP - Damage, 0, MaxHP);

	if (HP == 0)
	{
		Die(Damager);
	}
	else
	{
		OverrideAnimation(TEXT("Hit"));
		PlayHitSound();
	}

	if (MonsterComponent->GetMonsterSkin())
	{
		MonsterComponent->GetMonsterSkin()->OnHit(Damager);
	}

	OnReceiveDamage.Broadcast();
}