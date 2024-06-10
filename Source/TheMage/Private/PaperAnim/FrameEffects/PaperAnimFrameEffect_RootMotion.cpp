#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_RootMotion.h"
#include "PaperAnim/PaperAnimCharacter.h"
#include "PaperAnim/LogPaperAnim.h"
#include "GameFramework/RootMotionSource.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPaperAnimFrameEffect_RootMotion::Play_Implementation()
{
	RootMotionSourceSettingsFlags = ERootMotionSourceSettingsFlags::UseSensitiveLiftoffCheck;
	FinishVelocityMode = ERootMotionFinishVelocityMode::SetVelocity;
	AccumulateMode = ERootMotionAccumulateMode::Override;
	ApplyRootMotion(PaperAnimChar->GetActorForwardVector());
}

void UPaperAnimFrameEffect_RootMotion::ApplyRootMotion(const FVector& Direction, float Power, float Duration)
{
	if (RootMotionSourcePtr == nullptr)
	{
		RootMotionSourcePtr = MakeShared<FRootMotionSource_ConstantForce>( CreateRootMotionSourceInternal() );
		if (RootMotionSourcePtr == nullptr)
		{
			UE_LOG(LogPaperAnim,Warning,TEXT("The RootMotionSource %s does NOT created."), *GetClass()->GetFName().ToString());
			return;
		}
	}
	RootMotionSourcePtr->Force = Direction * ( Power > 0.f ? Power : DefaultPower );
	RootMotionSourcePtr->Duration = ( Duration > 0.f ? Duration : DefaultDuration );

	PaperAnimChar->GetCharacterMovement()->ApplyRootMotionSource(RootMotionSourcePtr);
}

FRootMotionSource_ConstantForce UPaperAnimFrameEffect_RootMotion::CreateRootMotionSourceInternal() const
{
	FRootMotionSource_ConstantForce Result;
	Result.InstanceName = RootMotionInstanceName;
	Result.Priority = RootMotionPriority;
	Result.StrengthOverTime = RootMotionStrengthOverTime;
	Result.Settings.SetFlag(RootMotionSourceSettingsFlags);
	Result.FinishVelocityParams.Mode = FinishVelocityMode;
	if (FinishVelocityMode == ERootMotionFinishVelocityMode::SetVelocity)
	{
		Result.FinishVelocityParams.SetVelocity = FVector::Zero();
	}
	Result.AccumulateMode = AccumulateMode;
	Result.Force = PaperAnimChar->GetActorForwardVector() * DefaultPower;
	Result.Duration = DefaultDuration;
	return Result;
}
