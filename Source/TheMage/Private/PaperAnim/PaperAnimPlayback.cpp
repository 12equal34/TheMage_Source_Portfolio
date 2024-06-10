#include "PaperAnim/PaperAnimPlayback.h"
#include "PaperFlipbook.h"

void FPaperAnimPlayback::Clear(UPaperFlipbook* InPF)
{
	check(InPF);
	PF = InPF;
	NumFrames = InPF->GetNumFrames();
	Frames  = 0.f;
	LoopCount = 0;
	KeyFrameIndex    = -1;
	KeyFrameRun      = 0.f;
}

float FPaperAnimPlayback::GetAnimLength() const 
{ 
	return PF->GetTotalDuration();
}

float FPaperAnimPlayback::GetFramesPerSecond() const 
{ 
	return PF->GetFramesPerSecond();
}

int32 FPaperAnimPlayback::GetNumKeyFrames() const 
{ 
	return PF->GetNumKeyFrames(); 
}

bool FPaperAnimPlayback::IsValidKeyFrameIndex() const
{ 
	return PF->IsValidKeyFrameIndex(KeyFrameIndex); 
}

const FPaperFlipbookKeyFrame& FPaperAnimPlayback::GetKeyFrameChecked() const
{ 
	return PF->GetKeyFrameChecked(KeyFrameIndex);
}

float FPaperAnimPlayback::GetLeftFramesInSeconds() const
{
	return GetLeftFrames() / GetFramesPerSecond();
}
