#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperAnimFlipbook.h"
#include "PaperAnimAsset.generated.h"


UCLASS(BlueprintType, Blueprintable)
class THEMAGE_API UPaperAnimAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<FName,FPaperAnimFlipbook> AnimMap;

public:
	UPaperAnimAsset();

	bool Contains(FName AnimName) const;

	const FPaperAnimFlipbook& GetAnimFlipbookChecked(FName AnimName);
	const FPaperAnimFlipbook* GetAnimFlipbook(FName AnimName);
};
