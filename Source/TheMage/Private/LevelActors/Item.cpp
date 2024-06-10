// By Gyeong-rok Min


#include "LevelActors/Item.h"
#include "Components/SphereComponent.h"
#include "Libraries/TheMageLibrary.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/ItemDataAsset.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComponent);
	UTheMageLibrary::SetItemCollision(SphereComponent);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->BodyInstance.bLockXRotation = true;
	SphereComponent->BodyInstance.bLockYRotation = true;
	SphereComponent->BodyInstance.bLockZRotation = true;
	SphereComponent->SetLinearDamping(0.f);
	
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(SphereComponent);
	UTheMageLibrary::SetNoCollision(Sprite);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemData && ItemData->ItemPF)
	{
		Sprite->SetFlipbook(ItemData->ItemPF);

		SphereComponent->SetSimulatePhysics(true);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
		SphereComponent->OnComponentHit.AddDynamic(this, &AItem::OnHit);
		SphereComponent->SetAllPhysicsLinearVelocity(VelocityOnBeginPlay);

		if (SoundOnBeginPlay)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundOnBeginPlay, GetActorLocation());
		}

		SetActorTickEnabled(true);
	}
	else
	{
		SetActorTickEnabled(false);
		SphereComponent->SetSimulatePhysics(false);
	}
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (UTheMageLibrary::HasPlayerTag(OtherActor))
	{
		if (UInventoryComponent* Inventory = OtherActor->GetComponentByClass<UInventoryComponent>())
		{
			const bool bSuccess = Inventory->PickUpItem(ItemData);
			if (bSuccess)
			{
				if (ItemData->PickUpSound)
				{
					UGameplayStatics::PlaySound2D(this, ItemData->PickUpSound);
				}
				Destroy();
			}
		}
	}
}

void AItem::OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit)
{
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic && GetVelocity().Z <= 0.f)
	{
		Sprite->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
		SphereComponent->SetSimulatePhysics(false);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Sprite->GetFlipbook())
	{
		if (SphereComponent->IsSimulatingPhysics())
		{
			const FRotator DeltaRotation = FRotator(DeltaTime * RotateRate, 0.f, 0.f);
			Sprite->AddWorldRotation(DeltaRotation);
		}
		else
		{
			FloatingTime += DeltaTime;
			const FVector FloatingOffset = FVector(0.f, 0.f, FloatingAmplitude * FMath::Sin(FloatingTime * FloatingRate));
			Sprite->SetRelativeLocation(FloatingOffset);
		}
	}
}

