// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PaperAnimFrameEffect.generated.h"

struct FPaperAnimPlayback;

UCLASS(BlueprintType, Blueprintable)
class THEMAGE_API UPaperAnimFrameEffect : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class APaperAnimCharacter> PaperAnimChar;

	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<const class UPaperAnimPlayer> PaperAnimPlayer;

public:
	void Init(APaperAnimCharacter* InPaperAnimChar);

	virtual void OnInit(APaperAnimCharacter* InPaperAnimChar) {}

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnInit"))
	void K2_OnInit();

	UFUNCTION(BlueprintNativeEvent)
	void Play();
};
