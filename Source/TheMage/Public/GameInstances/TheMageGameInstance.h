// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheMageGameInstance.generated.h"

class AMage;
/**
 * 
 */
UCLASS()
class THEMAGE_API UTheMageGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	static const FString MainSlotName;

public:
	//~ Begin UGameInstance Interface.
	virtual void Init() override;
	//~ End UGameInstance Interface.

	UFUNCTION(BlueprintCallable)
	void LoadMageSaveDatas(AMage* Mage);

	UFUNCTION(BlueprintCallable)
	void LoadLevelSaveDatas(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void SaveMageSaveDatas(AMage* Mage);

	UFUNCTION(BlueprintCallable)
	void SaveLevelSaveDatas(FName MapName);

	UFUNCTION(BlueprintCallable)
	void SaveGameToSlot();

	UFUNCTION(BlueprintCallable)
	void DeleteSaveGame();

protected:
	UPROPERTY()
	TObjectPtr<class UTheMageSaveGame> TheMageSaveGame;
};
