#include "PaperAnim/PaperAnimCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperAnim/PaperAnimPlayer.h"
#include "PaperAnim/PaperAnimAsset.h"
#include "PaperAnim/PaperAnimFlipbook.h"
#include "Components/CapsuleComponent.h"

APaperAnimCharacter::APaperAnimCharacter()
{
	GetSprite()->SetUsingAbsoluteRotation(true);
	AdjustSpriteLocationToBottomOfCapsule();
}

void APaperAnimCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimPlayer = NewObject<UPaperAnimPlayer>();
	AnimPlayer->SetPlaybackTarget(GetSprite());

	SetReverseFace(false);
	UpdateSpriteRotation();
}

void APaperAnimCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AnimAsset)
	{
		UpdateAnimation(DeltaSeconds);
	}
}

void APaperAnimCharacter::UpdateAnimation(float DeltaSeconds)
{
	AnimPlayer->TickPlayback(DeltaSeconds);

	if (IsOverridingAnim())
	{
		if (AnimPlayer->IsStopped())
		{
			SetOverridingAnim(false);
			AnimPlayer->Play();
		}
	}
	else
	{
		const FName AnimName = CalculateAnimation();

		if (CurrentAnimName != AnimName && AnimName != NAME_None)
		{
			CurrentAnimName = AnimName;
			const FPaperAnimFlipbook& AnimFlipbook = AnimAsset->GetAnimFlipbookChecked(CurrentAnimName);
			AnimPlayer->SetAnimFlipbook(AnimFlipbook);
			AnimPlayer->Play();
		}
	}
}

void APaperAnimCharacter::OverrideAnimation(FName AnimName)
{
	if (CurrentAnimName != AnimName)
	{
		const FPaperAnimFlipbook* AnimFlipbook = AnimAsset->GetAnimFlipbook(AnimName);
		if (AnimFlipbook && AnimFlipbook->PF)
		{
			SetOverridingAnim(true);
			AnimPlayer->Play();
			CurrentAnimName = AnimName;
			AnimPlayer->SetAnimFlipbook(*AnimFlipbook);
		}
	}
}

void APaperAnimCharacter::SetOverridingAnim(bool bInOverridingAnim)
{
	bIsOverridingAnim = bInOverridingAnim;
}

void APaperAnimCharacter::SetReverseFace(bool bInReverseFace)
{
	bReverseFace = bInReverseFace;
}

FVector APaperAnimCharacter::GetFaceVector() const
{
	return bRightFace ? FVector::XAxisVector : -FVector::XAxisVector;
}

FName APaperAnimCharacter::CalculateAnimation_Implementation()
{
	return NAME_None;
}

void APaperAnimCharacter::AdjustSpriteLocationToBottomOfCapsule()
{
	FVector SpriteLocation = GetSprite()->GetRelativeLocation();
	SpriteLocation.Z = -1.f * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	GetSprite()->SetRelativeLocation(SpriteLocation);
}

void APaperAnimCharacter::UpdateSpriteRotation()
{
	if (!FMath::IsNearlyZero(GetActorForwardVector().X))
	{
		const bool bRightControl = GetActorForwardVector().X > 0.f;
		bRightFace = ( bReverseFace ? !bRightControl : bRightControl );
		const FRotator SpriteRotation = bRightFace ? FRotator(0.f,0.f,0.f) : FRotator(0.f,180.f,0.f);
		GetSprite()->SetWorldRotation(SpriteRotation);
	}
}
