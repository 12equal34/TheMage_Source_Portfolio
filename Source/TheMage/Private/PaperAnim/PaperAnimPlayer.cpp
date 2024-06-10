#include "PaperAnim/PaperAnimPlayer.h"
#include "PaperAnim/PaperAnimPlayback.h"
#include "PaperAnim/PaperAnimFlipbook.h"
#include "PaperAnim/PaperAnimCharacter.h"
#include "paperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

void UPaperAnimPlayer::SetPlaybackTarget(UPaperFlipbookComponent* InPlaybackTarget)
{
	check(InPlaybackTarget);
	PlaybackTarget = InPlaybackTarget;
	PlaybackTarget->PlayFromStart();
	PlaybackTarget->Stop();
	PlaybackTarget->SetLooping(false);

	PlayRate = 1.f;
	bPlaying = true;
	bLooping = true;
}

void UPaperAnimPlayer::SetAnimFlipbook(const FPaperAnimFlipbook& InAnimFlipbook)
{
	Playback.Clear(InAnimFlipbook.PF);
	bLooping = InAnimFlipbook.bLooping;
	PlaybackTarget->SetFlipbook(InAnimFlipbook.PF);
	SetFrameEffects(InAnimFlipbook.FrameEffectInfos);
}

void UPaperAnimPlayer::SetFrameEffects(const TArray<FPaperAnimFrameEffectInfo>& InFrameEffectInfos)
{
	APaperAnimCharacter* AnimChar = Cast<APaperAnimCharacter>(PlaybackTarget->GetOwner());
	check(AnimChar);

	PlayingFrameEffects.Empty(PlayingFrameEffects.Num());
	for (const FPaperAnimFrameEffectInfo& FrameEffectInfo : InFrameEffectInfos)
	{
		UPaperAnimFrameEffect* FrameEffect = NewObject<UPaperAnimFrameEffect>(this, FrameEffectInfo.FrameEffectClass);
		FrameEffect->Init(AnimChar);

		const int32 KeyFrameIndex = FrameEffectInfo.StartEffectKeyFrame;
		FKeyFrameEffects& KeyFrameEffects = PlayingFrameEffects.FindOrAdd(KeyFrameIndex);
		KeyFrameEffects.Array.Add(FrameEffect);
	}
}

void UPaperAnimPlayer::PlayFrameEffects(int32 KeyFrameIndex)
{
	if (PlayingFrameEffects.Contains(KeyFrameIndex))
	{
		for (UPaperAnimFrameEffect* FrameEffect : PlayingFrameEffects[KeyFrameIndex].Array)
		{
			FrameEffect->Play();
		}
	}
}

void UPaperAnimPlayer::TickPlayback(float DeltaTime)
{
	if (!bPlaying || !Playback.PF) return;

	const float DeltaFrames = DeltaTime * GetPlayerFramesPerSecond();

	Playback.Frames      += DeltaFrames;
	Playback.KeyFrameRun += DeltaFrames;

	// If the playback begins play then init the key frame variables.
	if ( Playback.KeyFrameIndex == -1 )
	{
		Playback.KeyFrameIndex = 0;
		PlayFrameEffects(Playback.KeyFrameIndex);
	}

	// Calculate what key frame is playing, as to frame unit.
	if ( Playback.IsValidKeyFrameIndex() )
	{
		const FPaperFlipbookKeyFrame* CurrentKeyFrame = &Playback.GetKeyFrameChecked();

		while ( CurrentKeyFrame && CurrentKeyFrame->FrameRun < Playback.KeyFrameRun )
		{
			// finish the current key frame.
			Playback.KeyFrameRun -= CurrentKeyFrame->FrameRun;
			
			// set the next key frame.
			Playback.KeyFrameIndex++;
			if ( Playback.IsValidKeyFrameIndex() )
			{
				CurrentKeyFrame = &Playback.GetKeyFrameChecked();
			}
			else if (bLooping)
			{
				Playback.LoopCount++;
				Playback.Frames -= Playback.NumFrames;
				Playback.KeyFrameIndex = 0;
				CurrentKeyFrame = &Playback.GetKeyFrameChecked();
				Event.Broadcast(EPaperAnimPlayerEvent::EPAPE_OnLoop);
			}
			else
			{
				CurrentKeyFrame = nullptr;
				Playback.KeyFrameRun = 0.f;
				Playback.Frames = Playback.NumFrames;
				bPlaying = false;
				Event.Broadcast(EPaperAnimPlayerEvent::EPAPE_OnEnd);
			}

			PlayFrameEffects(Playback.KeyFrameIndex);
		}
	}

	PlaybackTarget->SetNewTime( Playback.Frames / GetPlayerFramesPerSecond() );
}

void UPaperAnimPlayer::SetPlayRate(float NewPlayRate)
{
	check(NewPlayRate > 0.f);
	PlayRate = NewPlayRate;
}

void UPaperAnimPlayer::Play()
{
	bPlaying = true;
}

void UPaperAnimPlayer::Stop()
{
	bPlaying = false;
}

void UPaperAnimPlayer::SetLooping(bool bInLooping)
{
	bLooping = bInLooping;
}

float UPaperAnimPlayer::GetPlayerFramesPerSecond() const
{
	return Playback.GetFramesPerSecond() * PlayRate;
}

float UPaperAnimPlayer::GetAnimLength() const 
{ 
	return Playback.GetAnimLength();
}

float UPaperAnimPlayer::GetFramesPerSecond() const 
{ 
	return Playback.GetFramesPerSecond();
}

int32 UPaperAnimPlayer::GetNumKeyFrames() const 
{ 
	return Playback.GetNumKeyFrames(); 
}

bool UPaperAnimPlayer::IsValidKeyFrameIndex() const
{ 
	return Playback.IsValidKeyFrameIndex(); 
}

const FPaperFlipbookKeyFrame& UPaperAnimPlayer::GetKeyFrameChecked() const
{ 
	return Playback.GetKeyFrameChecked();
}

float UPaperAnimPlayer::GetLeftFramesInSeconds() const
{
	return Playback.GetLeftFramesInSeconds();
}

