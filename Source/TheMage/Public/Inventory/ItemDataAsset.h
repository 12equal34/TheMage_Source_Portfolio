// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EItemType: uint8
{
	EIT_None,
	EIT_Money,
	EIT_Material,
};


/**
 * 
 */
UCLASS()
class THEMAGE_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere)
	FText ItemText;

	UPROPERTY(EditAnywhere)
	FText DescriptionText;

	UPROPERTY(EditAnywhere)
	EItemType ItemType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPaperFlipbook> ItemPF;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundBase> PickUpSound;

	UPROPERTY(EditAnywhere)
	int32 Value;

};
