// By Gyeong-rok Min

#include "LevelActors/Portal.h"
#include "Components/CapsuleComponent.h"
#include "Libraries/TheMageLibrary.h"
#include "Characters/Mage.h"
#include "GameInstances/TheMageGameInstance.h"
#include "Kismet/GameplayStatics.h"


APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	SetRootComponent(CapsuleComponent);
	UTheMageLibrary::SetPlayerPawnDetectorCollision(CapsuleComponent);
	CapsuleComponent->SetGenerateOverlapEvents(true);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	if (PortalMapName != NAME_None)
	{
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnCapsuleBeginOverlap);
	}
}

void APortal::OnPortalEnter_Implementation(AMage* InMage)
{
	if (UTheMageGameInstance* TheMageGameInstance = Cast<UTheMageGameInstance>(GetGameInstance()))
	{
		if (bAutoSaveOnEnter)
		{
			TheMageGameInstance->SaveMageSaveDatas(InMage);
			TheMageGameInstance->SaveLevelSaveDatas(PortalMapName);
			TheMageGameInstance->SaveGameToSlot();
		}

		UGameplayStatics::OpenLevel(this, PortalMapName);
	}
}

void APortal::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (UTheMageLibrary::HasPlayerTag(OtherActor))
	{
		if (AMage* Mage = Cast<AMage>(OtherActor))
		{
			OnPortalEnter(Mage);
		}
	}
}
