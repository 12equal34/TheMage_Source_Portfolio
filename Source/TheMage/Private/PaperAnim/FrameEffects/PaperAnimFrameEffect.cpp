// By Gyeong-rok Min


#include "PaperAnim/FrameEffects/PaperAnimFrameEffect.h"
#include "PaperAnim/PaperAnimCharacter.h"
#include "PaperAnim/PaperAnimPlayer.h"

void UPaperAnimFrameEffect::Init(APaperAnimCharacter* InPaperAnimChar)
{
	check(InPaperAnimChar && InPaperAnimChar->GetAnimPlayer());

	PaperAnimChar = InPaperAnimChar;
	PaperAnimPlayer = InPaperAnimChar->GetAnimPlayer();

	OnInit(InPaperAnimChar);
	K2_OnInit();
}

void UPaperAnimFrameEffect::Play_Implementation()
{
}