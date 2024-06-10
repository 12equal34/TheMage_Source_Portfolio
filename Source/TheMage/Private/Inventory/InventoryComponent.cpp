// By Gyeong-rok Min


#include "Inventory/InventoryComponent.h"
#include "Inventory/ItemDataAsset.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool UInventoryComponent::PickUpItem(UItemDataAsset* ItemData)
{
	check(ItemData);

	if (ItemData->ItemType == EItemType::EIT_Money)
	{
		const int32 OldMoney = Money;
		Money = OldMoney + ItemData->Value;
		OnMoneyChanged.Broadcast(OldMoney, Money);
		return true;
	}

	return false;
}

void UInventoryComponent::SetMoney(int32 InMoney)
{
	check(InMoney >= 0);
	if (Money != InMoney)
	{
		const int32 OldMoney = Money;
		Money = InMoney;
		OnMoneyChanged.Broadcast(OldMoney, Money);
	}
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

