#pragma once

#include "CoreMinimal.h"
#include "PaperAnimPlayback.generated.h"

class UPaperFlipbook;
struct FPaperFlipbookKeyFrame;


USTRUCT(BlueprintType)
struct FPaperAnimPlayback
{
	GENERATED_BODY()

	friend class UPaperAnimPlayer;

protected:
	UPROPERTY(BlueprintReadOnly)
	UPaperFlipbook* PF;

	UPROPERTY(BlueprintReadOnly)
	float Frames;

	UPROPERTY(BlueprintReadOnly)
	int32 LoopCount;

	UPROPERTY(BlueprintReadOnly)
	int32 NumFrames;

	UPROPERTY(BlueprintReadOnly)
	int32 KeyFrameIndex;

	UPROPERTY(BlueprintReadOnly)
	float KeyFrameRun;

	void Clear(UPaperFlipbook* InPF);

public:
	FORCEINLINE int32 GetNumFrames() const { return NumFrames; }
	FORCEINLINE float GetFrames() const { return Frames; }
	FORCEINLINE int32 GetLoopCount() const { return LoopCount; }
	FORCEINLINE int32 GetKeyFrameIndex() const { return KeyFrameIndex; }
	FORCEINLINE float GetKeyFrameRun() const { return KeyFrameRun; }
	FORCEINLINE float GetLeftFrames() const { return NumFrames - Frames; }

	float GetAnimLength() const;
	float GetFramesPerSecond() const;
	int32 GetNumKeyFrames() const;
	bool  IsValidKeyFrameIndex() const;
	const FPaperFlipbookKeyFrame& GetKeyFrameChecked() const;
	float GetLeftFramesInSeconds() const;
};
