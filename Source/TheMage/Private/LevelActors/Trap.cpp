// By Gyeong-rok Min


#include "LevelActors/Trap.h"
#include "Components/BoxComponent.h"
#include "Libraries/TheMageLibrary.h"
#include "Characters/BaseCharacter.h"

ATrap::ATrap()
{
	PrimaryActorTick.bCanEverTick = false;

	TrapRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TrapRoot"));
	SetRootComponent(TrapRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp01"));
	BoxComponent->SetupAttachment(TrapRoot);
	UTheMageLibrary::SetPlayerBodyDetectorCollision(BoxComponent);
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrap::OnBoxBeginOverlap);
}

void ATrap::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (UTheMageLibrary::HasPlayerTag(OtherActor))
	{
		ABaseCharacter* BaseChar = Cast<ABaseCharacter>(OtherActor);
		if (BaseChar && BaseChar->CanReceiveDamage())
		{
			const FVector ToBaseChar = (BaseChar->GetActorLocation() - GetActorLocation()).GetUnsafeNormal2D();
			const FVector Impulse  = ToBaseChar * TrapInfo.HorizontalKnockbackPower + FVector::UpVector * TrapInfo.VerticalKnockbackPower;
			BaseChar->Knockback(TrapInfo.KnockbackTime, Impulse);
			BaseChar->ReceiveDamage(TrapInfo.Damage, nullptr);

			K2_OnTrapped(BaseChar);
		}
	}
}
