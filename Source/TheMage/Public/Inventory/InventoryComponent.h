// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoneyChangedDelegate, int32, OldMoney, int32, NowMoney);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEMAGE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 Money;

	UPROPERTY(BlueprintAssignable)
	FOnMoneyChangedDelegate OnMoneyChanged;

public:	
	UInventoryComponent();

	bool PickUpItem(class UItemDataAsset* ItemData);

	void SetMoney(int32 InMoney);

	FORCEINLINE int32 GetMoney() const { return Money; }
	FORCEINLINE FOnMoneyChangedDelegate& GetOnMoneyChangedDelegate() { return OnMoneyChanged; }

protected:
	virtual void BeginPlay() override;

};
