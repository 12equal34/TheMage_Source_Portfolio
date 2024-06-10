// By Gyeong-rok Min


#include "GameInstances/TheMageGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGames/TheMageSaveGame.h"
#include "Characters/Mage.h"
#include "Components/HPComponent.h"
#include "Inventory/InventoryComponent.h"

const FString UTheMageGameInstance::MainSlotName = TEXT("MainSlot");

void UTheMageGameInstance::Init()
{
	Super::Init();

	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(MainSlotName, 0);
	if (!SaveGame)
	{
		SaveGame = UGameplayStatics::CreateSaveGameObject(UTheMageSaveGame::StaticClass());
		checkf(SaveGame, TEXT("SaveGame isn't created."));
	}

	TheMageSaveGame = Cast<UTheMageSaveGame>(SaveGame);
	checkf(TheMageSaveGame, TEXT("SaveGame should be inherited from UTheMageSaveGame."));
}

void UTheMageGameInstance::LoadMageSaveDatas(AMage* Mage)
{
	// load the mage character datas.
	const int32 MaxHP = TheMageSaveGame->MageSaveDatas.MaxHP;
	const int32 HP    = TheMageSaveGame->MageSaveDatas.HP;
	const TArray<EAuraType>& Auras = TheMageSaveGame->MageSaveDatas.Auras;
	Mage->SetMaxHP(MaxHP);
	Mage->SetHP(HP);
	Mage->SetAuras(Auras);

	// load the inventory datas.
	const int32 Money = TheMageSaveGame->InventorySaveDatas.Money;
	Mage->GetInventoryComponent()->SetMoney(Money);
}

void UTheMageGameInstance::LoadLevelSaveDatas(const UObject* WorldContextObject)
{
	if (!TheMageSaveGame)
	{
		USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UTheMageSaveGame::StaticClass());
		checkf(SaveGame, TEXT("SaveGame isn't created."));
		TheMageSaveGame = Cast<UTheMageSaveGame>(SaveGame);
		checkf(TheMageSaveGame, TEXT("SaveGame should be inherited from UTheMageSaveGame."));
	}
	
	UGameplayStatics::OpenLevel(WorldContextObject, TheMageSaveGame->LevelSaveDatas.SaveMapName);
}

void UTheMageGameInstance::SaveMageSaveDatas(AMage* Mage)
{
	if (TheMageSaveGame)
	{
		TheMageSaveGame->MageSaveDatas.MaxHP = Mage->GetMaxHP();
		TheMageSaveGame->MageSaveDatas.HP = Mage->GetHP();
		TheMageSaveGame->MageSaveDatas.Auras = Mage->GetAuras();
		TheMageSaveGame->InventorySaveDatas.Money = Mage->GetInventoryComponent()->GetMoney();
	}
	
}

void UTheMageGameInstance::SaveLevelSaveDatas(FName MapName)
{
	if (TheMageSaveGame)
	{
		TheMageSaveGame->LevelSaveDatas.SaveMapName = MapName;
	}
}

void UTheMageGameInstance::SaveGameToSlot()
{
	if (TheMageSaveGame)
	{
		UGameplayStatics::SaveGameToSlot(TheMageSaveGame, MainSlotName, 0);
	}
}

void UTheMageGameInstance::DeleteSaveGame()
{
	if (TheMageSaveGame)
	{
		UGameplayStatics::DeleteGameInSlot(MainSlotName, 0);
		TheMageSaveGame = nullptr;
	}
}
