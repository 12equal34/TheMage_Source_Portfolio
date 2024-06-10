#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_Dash.h"
#include "Characters/BasePlayerCharacter.h"
#include "Components/WallClimbingComponent.h"
#include "PaperAnim/PaperAnimPlayer.h"

UPaperAnimFrameEffect_Dash::UPaperAnimFrameEffect_Dash()
{
	DefaultPower = 2700.f;
}

void UPaperAnimFrameEffect_Dash::OnInit(APaperAnimCharacter* InPaperAnimChar)
{
	PlayerChar = Cast<ABasePlayerCharacter>(InPaperAnimChar);
	check(PlayerChar.IsValid());
}

void UPaperAnimFrameEffect_Dash::Play_Implementation()
{
	FVector Direction = PlayerChar->GetFaceVector();
	if (PlayerChar->GetWallClimbingComponent()->IsClimbingWall())
	{
		PlayerChar->SetActorRotation(Direction.Rotation());
		PlayerChar->UpdateSpriteRotation();
	}
	else if (!PlayerChar->GetMoveInput().IsNearlyZero())
	{
		Direction = PlayerChar->GetMoveInput().GetUnsafeNormal();
		PlayerChar->SetActorRotation(Direction.Rotation());
		PlayerChar->UpdateSpriteRotation();
	}
	
	const float Power = DefaultPower * PaperAnimPlayer->GetPlayRate();
	const float Duration = PaperAnimPlayer->GetLeftFramesInSeconds();
	ApplyRootMotion(Direction, Power, Duration);
}

