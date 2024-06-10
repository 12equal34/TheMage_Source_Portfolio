#include "PaperAnim/FrameEffects/PaperAnimFrameEffect_DestroyOwner.h"
#include "PaperAnim/PaperAnimCharacter.h"

void UPaperAnimFrameEffect_DestroyOwner::Play_Implementation()
{
	PaperAnimChar->Destroy();
}
