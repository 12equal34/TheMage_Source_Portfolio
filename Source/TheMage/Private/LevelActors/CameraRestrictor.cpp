
#include "LevelActors/CameraRestrictor.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Controllers/MagePlayerController.h"
#include "Interfaces/CameraRestrictorInterface.h"
#include "Libraries/TheMageLibrary.h"

ACameraRestrictor::ACameraRestrictor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraDetector"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetBoxExtent(FVector(400.f, 100.f, 300.f));
	UTheMageLibrary::SetPlayerPawnDetectorCollision(BoxComponent);

	CameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPosition"));
	CameraPosition->SetupAttachment(BoxComponent);

#if WITH_EDITORONLY_DATA
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("CameraPosBillboard"));
	BillboardComponent->SetupAttachment(CameraPosition);
#endif // WITH_EDITORONLY_DATA
}

FVector ACameraRestrictor::GetCamreaPosition() const
{
	return CameraPosition->GetComponentLocation();
}

void ACameraRestrictor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACameraRestrictor::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACameraRestrictor::OnBoxEndOverlap);
}

void ACameraRestrictor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		APawn* PlayerPawn = Cast<APawn>(OtherActor);
		if (!PlayerPawn) return;

		AMagePlayerController* Controller = Cast<AMagePlayerController>(PlayerPawn->GetController());
		if (Controller && Controller->Implements<UCameraRestrictorInterface>())
		{
			CameraRestrictedInterface = TScriptInterface<ICameraRestrictorInterface>(Controller);
			ICameraRestrictorInterface::Execute_SetOverlappingCameraRestrictor(Controller, this);
		}
	}
}

void ACameraRestrictor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if (!CameraRestrictedInterface.GetObject()) return;

	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		APawn* PlayerPawn = Cast<APawn>(OtherActor);
		if (!PlayerPawn) return;

		AController* Controller = PlayerPawn->GetController();
		if (Controller == CameraRestrictedInterface.GetObject())
		{
			ICameraRestrictorInterface::Execute_SetOverlappingCameraRestrictor(Controller, nullptr);
			CameraRestrictedInterface = nullptr;
		}
	}
}
