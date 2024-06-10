#include "Characters/BaseCharacter.h"
#include "Components/PositionGuideComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Libraries/TheMageLibrary.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	/**
	* Create Default Subobjects.
	*/
	PositionGuide = CreateDefaultSubobject<UPositionGuideComponent>(TEXT("PositionGuide0"));
	PositionGuide->SetupAttachment(GetCapsuleComponent());
	PositionGuide->SetRelativeLocation(FVector(0.f, 0.f, -1.f * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	PositionGuide->SetTargetCapsule(GetCapsuleComponent());

	Connector = CreateDefaultSubobject<USphereComponent>(TEXT("Connector"));
	Connector->SetupAttachment(GetRootComponent());
}

void ABaseCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CacheInitDatas();
	BindOverlapEvents();
	HealFully();
}

void ABaseCharacter::Move(FVector WorldDirection,float ScaleValue)
{
	MoveInput = WorldDirection * ScaleValue;
	MoveInput.Z = 0.f;
	if (MoveInput.IsNearlyZero()) return;

	if (CanMove())
	{
		SetActorRotation(MoveInput.Rotation());
		UpdateSpriteRotation();
		GetCharacterMovement()->AddInputVector(MoveInput);
	}
}

void ABaseCharacter::SetZeroFallingLateralFriction(float Duration)
{
	GetWorldTimerManager().SetTimer(RestoreFallingLateralFrictionTimer, this, &ABaseCharacter::RestoreFallingLateralFriction, Duration, false);
	GetCharacterMovement()->FallingLateralFriction = 0.f;
}

void ABaseCharacter::RestoreFallingLateralFriction()
{
	GetCharacterMovement()->FallingLateralFriction = InitFallingLateralFriction;
}

void ABaseCharacter::EnableMove()
{
	bCanMove = true;
}

void ABaseCharacter::MakeInvincible(float Duration)
{
	if (Duration > 0.f)
	{
		SetInvincible(true);
		FTimerDelegate DisableInvincibleDelegate;
		DisableInvincibleDelegate.BindUObject(this, &ABaseCharacter::SetInvincible, false);
		GetWorldTimerManager().SetTimer(InvincibleTimer, DisableInvincibleDelegate, Duration, false);
		K2_OnMadeInvincible(Duration);
	}
}

void ABaseCharacter::MakeInvincibleByHit()
{
	MakeInvincible(InvincibleDurationByHit);
}

bool ABaseCharacter::CanReceiveDamage() const
{
	return !IsInvincible() && !IsDead();
}

void ABaseCharacter::OverrideAnimation(FName AnimName)
{
	if (!IsDead() || AnimName == TEXT("Die"))
	{
		Super::OverrideAnimation(AnimName);
	}
}

void ABaseCharacter::CacheInitDatas()
{
	InitFallingLateralFriction = GetCharacterMovement()->FallingLateralFriction;
	InitCapsuleHalfHeight      = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	InitCapsuleRadius          = GetCapsuleComponent()->GetUnscaledCapsuleRadius();
}

void ABaseCharacter::BindOverlapEvents()
{
	GetConnector()->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnConnectorBeginOverlap);
	GetConnector()->OnComponentEndOverlap.AddDynamic(this, &ABaseCharacter::OnConnectorEndOverlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnCapsuleBeginOverlap);
	GetSprite()->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnSpriteBeginOverlap);
}

void ABaseCharacter::Knockback(float KnockbackTime, const FVector& Impulse)
{
	const bool bIsFlying = GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying;
	if (bIsFlying)
	{
		const bool bVelocityChange = true;
		GetCharacterMovement()->AddImpulse(Impulse, bVelocityChange);
	}
	else
	{
		const bool bXYOverride = true;
		const bool bZOverride = true;
		LaunchCharacter(Impulse, bXYOverride, bZOverride);
	}
	OnKnockbacked(KnockbackTime);
}

void ABaseCharacter::OnKnockbacked_Implementation(float KnockbackTime)
{
	if (KnockbackTime > 0.f)
	{
		MakeCantMove(KnockbackTime);
		SetZeroFallingLateralFriction(KnockbackTime);
	}
}

void ABaseCharacter::MakeCantMove(float Duration)
{
	if (Duration > 0.f)
	{
		bCanMove = false;
		GetWorldTimerManager().SetTimer(EnableMoveTimer, this, &ABaseCharacter::EnableMove, Duration, false);
	}
}

void ABaseCharacter::Die(ABaseCharacter* Damager)
{
	GetWorldTimerManager().ClearTimer(EnableMoveTimer);
	GetWorldTimerManager().ClearTimer(InvincibleTimer);

	bCanMove = false;
	SetInvincible(true);

	bDead = true;
	OverrideAnimation(TEXT("Die"));
	K2_OnDie(Damager);
	PlayDieSound();
}

void ABaseCharacter::PlayHitSound() const
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
	}
}

void ABaseCharacter::PlayDieSound() const
{
	if (DieSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,DieSound,GetActorLocation());
	}
}

void ABaseCharacter::HealFully()
{
	HP = MaxHP;
}

void ABaseCharacter::SetHP(int32 InHP)
{
	check(InHP >= 0);
	HP = InHP;
}

void ABaseCharacter::SetMaxHP(int32 InMaxHP)
{
	check(InMaxHP > 0);
	MaxHP = InMaxHP;
	if (HP > MaxHP)
	{
		HP = MaxHP;
	}
}
