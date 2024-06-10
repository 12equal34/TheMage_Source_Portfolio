#include "Monster/MonsterComponent.h"
#include "Monster/MonsterCharacter.h"
#include "Monster/Decision/MonsterBrain.h"
#include "Monster/Perception/MonsterSight.h"
#include "Monster/Perception/MonsterSkin.h"

UMonsterComponent::UMonsterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.SetTickFunctionEnable(false);
}

void UMonsterComponent::CreateMonsterBrain()
{
	if (BrainClass)
	{
		Brain = NewObject<UMonsterBrain>(this,*BrainClass);
		Brain->Init(MonsterOwner);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No monster brain class defined on '%s'."), *GetName());
	}
}

void UMonsterComponent::CreateMonsterSight()
{
	if (SightClass)
	{
		Sight = NewObject<UMonsterSight>(this,*SightClass);
		Sight->Init(MonsterOwner);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No monster Sight class defined on '%s'."), *GetName());
	}
}

void UMonsterComponent::CreateMonsterSkin()
{
	if (SkinClass)
	{
		Skin = NewObject<UMonsterSkin>(this,*SkinClass);
		Skin->Init(MonsterOwner);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No monster Skin class defined on '%s'."), *GetName());
	}
}

void UMonsterComponent::BeginPlay()
{
	Super::BeginPlay();

	AMonsterCharacter* MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());
	checkf(MonsterCharacter, TEXT("The owner of UMonsterComponent must be inherited from AMonsterCharacter."));
	Init(MonsterCharacter);
}

void UMonsterComponent::Init(AMonsterCharacter* InMonsterOwner)
{
	check(InMonsterOwner);
	MonsterOwner = InMonsterOwner;
	CreateMonsterBrain();
	CreateMonsterSight();
	CreateMonsterSkin();
}

void UMonsterComponent::TickMonster(float DeltaSeconds)
{
	if (!Brain)
	{
		return;
	}

	if (Sight)
	{
#if WITH_EDITORONLY_DATA
		if (bDrawDebug)
		{
			Sight->DrawDebugSightCone();
		}
#endif

		TArray<AActor*> ActorsInSight;

		for (AActor* ConnectedActor : MonsterOwner->GetConnectedActors())
		{
			if (Sight->IsVisible(ConnectedActor))
			{
				ActorsInSight.Add(ConnectedActor);
			}
		}

		Brain->ActorsInSight = ActorsInSight;
	}

	if (Skin)
	{
		Brain->bPerceivedUnderAttack = Skin->IsPainful();
	}

	Brain->Tick(DeltaSeconds);
}

