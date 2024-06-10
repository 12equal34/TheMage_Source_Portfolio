// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGames/LevelSaveDatas.h"
#include "SaveGames/MageSaveDatas.h"
#include "SaveGames/InventorySaveDatas.h"
#include "TheMageSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class THEMAGE_API UTheMageSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FLevelSaveDatas LevelSaveDatas;

	UPROPERTY()
	FMageSaveDatas MageSaveDatas;

	UPROPERTY()
	FInventorySaveDatas InventorySaveDatas;

public:
	UTheMageSaveGame();
};
