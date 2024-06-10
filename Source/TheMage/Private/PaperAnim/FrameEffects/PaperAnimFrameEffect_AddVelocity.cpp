// By Gyeong-rok Min


#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_AddVelocity.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPaperAnimFrameEffect_AddVelocity::OnInit(APaperAnimCharacter* InPaperAnimChar)
{
	BaseChar = Cast<ABaseCharacter>(InPaperAnimChar);
	check(BaseChar.IsValid());
}

void UPaperAnimFrameEffect_AddVelocity::Play_Implementation()
{
	const FVector FrontVector = BaseChar->GetFaceVector();

	FVector Direction = FVector::ZeroVector;
	switch (AddVelocityType)
	{
	case EAddVelocityType::EAVT_Front:
		Direction = FrontVector;
		break;
	case EAddVelocityType::EAVT_Back:
		Direction = -FrontVector;
		break;
	case EAddVelocityType::EAVT_Left:
		Direction = FrontVector ^ FVector::ZAxisVector;
		break;
	case EAddVelocityType::EAVT_Right:
		Direction = FVector::ZAxisVector ^ FrontVector;
		break;
	case EAddVelocityType::EAVT_InputDirection:
		Direction = BaseChar->GetMoveInput();
		break;
	default:
		return;
	}

	if (Direction != FVector::ZeroVector)
	{
		const FVector DeltaVelocity = Direction * Speed;
		PaperAnimChar->GetCharacterMovement()->AddImpulse(DeltaVelocity, true);
	}
}
