#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_WallJump.h"
#include "PaperAnim/PaperAnimPlayer.h"
#include "Characters/BaseCharacter.h"

UPaperAnimFrameEffect_WallJump::UPaperAnimFrameEffect_WallJump()
{
}

void UPaperAnimFrameEffect_WallJump::OnInit(APaperAnimCharacter* InPaperAnimChar)
{
	BaseChar = Cast<ABaseCharacter>(InPaperAnimChar);
	check(BaseChar.IsValid());
}

void UPaperAnimFrameEffect_WallJump::Play_Implementation()
{
	BaseChar->MakeCantMove(CantMoveTimer);
	BaseChar->SetZeroFallingLateralFriction(RestoreFallingLateralFrictionTimer);
	const FVector LaunchVelocity = FVector(HorizontalLaunchVelocity * (BaseChar->IsRightFace() ? 1.f : -1.f),
										   0.f, VerticalLaunchVelocity);
	BaseChar->LaunchCharacter(LaunchVelocity, true, true);
	BaseChar->SetActorRotation(BaseChar->GetFaceVector().Rotation());
}
