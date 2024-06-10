#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PaperAnimPlayback.h"
#include "PaperAnimPlayer.generated.h"

class UPaperFlipbook;
class UPaperAnimFrameEffect;
struct FPaperAnimFlipbook;
struct FPaperAnimFrameEffectInfo;

UENUM(BlueprintType)
enum class EPaperAnimPlayerEvent : uint8
{
	EPAPE_OnEnd,
	EPAPE_OnLoop,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPaperAnimPlayerDelegate, EPaperAnimPlayerEvent, EventType);

USTRUCT()
struct FKeyFrameEffects
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<UPaperAnimFrameEffect>> Array;
};


UCLASS(BlueprintType)
class THEMAGE_API UPaperAnimPlayer : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient)
	TObjectPtr<class UPaperFlipbookComponent> PlaybackTarget;

	FPaperAnimPlayback Playback;

	UPROPERTY(Transient)
	TMap<int32, FKeyFrameEffects> PlayingFrameEffects;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bPlaying;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bLooping;

	UPROPERTY(Transient, BlueprintReadOnly)
	float PlayRate = 1.f;

public:
	UPROPERTY(BlueprintAssignable)
	FPaperAnimPlayerDelegate Event;

	void TickPlayback(float DeltaTime);

protected:
	void PlayFrameEffects(int32 KeyFrameIndex);

private:
	void SetFrameEffects(const TArray<FPaperAnimFrameEffectInfo>& InFrameEffectInfos);

public:
	void SetPlaybackTarget(UPaperFlipbookComponent* InPlaybackTarget);
	void SetAnimFlipbook(const FPaperAnimFlipbook& InAnimFlipbook);
	void SetPlayRate(float NewPlayRate);

	UFUNCTION(BlueprintCallable)
	void Play();

	UFUNCTION(BlueprintCallable)
	void Stop();

	UFUNCTION(BlueprintCallable)
	void SetLooping(bool bInLooping);

public:
	float GetPlayerFramesPerSecond() const;

	FORCEINLINE UPaperFlipbookComponent* GetPlaybackTarget() const { return PlaybackTarget; }
	FORCEINLINE bool IsPlaying() const { return bPlaying; }
	FORCEINLINE bool IsStopped() const { return !bPlaying; }
	FORCEINLINE bool IsLooping() const { return bLooping; }
	FORCEINLINE float GetPlayRate() const { return PlayRate; }
	FORCEINLINE const FPaperAnimPlayback& GetPlayback() const { return Playback; }

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetNumFrames() const { return Playback.NumFrames; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetFrames() const { return Playback.Frames; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetLoopCount() const { return Playback.LoopCount; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetKeyFrameIndex() const { return Playback.KeyFrameIndex; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetKeyFrameRun() const { return Playback.KeyFrameRun; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetLeftFrames() const { return Playback.NumFrames - Playback.Frames; }

	UFUNCTION(BlueprintPure)
	float GetAnimLength() const;

	UFUNCTION(BlueprintPure)
	float GetFramesPerSecond() const;

	UFUNCTION(BlueprintPure)
	int32 GetNumKeyFrames() const;

	UFUNCTION(BlueprintPure)
	bool  IsValidKeyFrameIndex() const;

	const FPaperFlipbookKeyFrame& GetKeyFrameChecked() const;

	UFUNCTION(BlueprintPure)
	float GetLeftFramesInSeconds() const;
};

