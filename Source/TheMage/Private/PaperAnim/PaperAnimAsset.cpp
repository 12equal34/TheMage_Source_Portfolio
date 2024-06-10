#include "PaperAnim/PaperAnimAsset.h"

UPaperAnimAsset::UPaperAnimAsset()
{
}

bool UPaperAnimAsset::Contains(FName AnimName) const
{
	return AnimMap.Contains(AnimName);
}

const FPaperAnimFlipbook& UPaperAnimAsset::GetAnimFlipbookChecked(FName AnimName)
{
	const FPaperAnimFlipbook* FoundAnimFlipbook = GetAnimFlipbook(AnimName);
	checkf(FoundAnimFlipbook && FoundAnimFlipbook->PF, TEXT("The paper anim asset hasn't the anim flipbook which of name is %s"), *AnimName.ToString());
	return *FoundAnimFlipbook;
}

const FPaperAnimFlipbook* UPaperAnimAsset::GetAnimFlipbook(FName AnimName)
{
	return AnimMap.Find(AnimName);
}
