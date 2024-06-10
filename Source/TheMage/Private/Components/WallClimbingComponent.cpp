#include "Components/WallClimbingComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "KismetTraceUtils.h"

UWallClimbingComponent::UWallClimbingComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UWallClimbingComponent::InitializeComponent()
{
	Super::InitializeComponent();

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	checkf(Character, TEXT("The owner of UWallClimbingComponent must be inherited from ACharacter."));
	Init(Character);
}

void UWallClimbingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TargetCharacter)
	{
		CapsuleRadiusOnBeginPlay = TargetCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	}
}

void UWallClimbingComponent::Init(ACharacter* InTargetCharacter)
{
	TargetCharacter = InTargetCharacter;
}

void UWallClimbingComponent::TryClimbWall(const FVector& MoveInput)
{
	checkf(TargetCharacter, TEXT("The target character isn't set."));

	if (FMath::IsNearlyZero(MoveInput.X))
	{
		TransferNotClimbingWallState();
		return;
	}

	// Always try sliding when player is falling.
	const float FallingVelocity = TargetCharacter->GetVelocity().Z;
	if (FallingVelocity > -MinVelocityToClimbWall)
	{
		TransferNotClimbingWallState();
		return;
	}

	// And needs to input keeping.
	const float DirectionToWallIfExists = TargetCharacter->GetActorForwardVector().X;
	const bool bWallAndInputValueAreSameDirection = 0.f < MoveInput.X * DirectionToWallIfExists;
	if (!bWallAndInputValueAreSameDirection) 
	{
		TransferNotClimbingWallState();
		return;
	}

	UWorld* const World = TargetCharacter->GetWorld();
	check(World);

	// Is there a wall?
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic); // We assumes any ECC_WorldStatic is Wall Type.
	FVector Start = TargetCharacter->GetActorLocation();
	FVector End   = Start + TargetCharacter->GetActorForwardVector() * TraceLengthToClimbWall;
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(TargetCharacter);
	const bool bThereIsWall = World->LineTraceSingleByObjectType(HitResult,Start,End,ObjectQueryParams,CollisionQueryParams);

#if WITH_EDITORONLY_DATA && ENABLE_DRAW_DEBUG
	if (bDrawDebugTraceTryingClimbWall)
	{
		::DrawDebugLineTraceSingle(World, Start, End, EDrawDebugTrace::ForOneFrame, bThereIsWall, HitResult, FLinearColor::Green, FLinearColor::Red, 0.f);
	}
#endif

	if (!bThereIsWall)
	{
		TransferNotClimbingWallState();
		return;
	}
	// DirectionToWall = DirectionToWallIfExists > 0.f;

	// Slide the wall.
	UCharacterMovementComponent* MovementComp = TargetCharacter->GetCharacterMovement();
	MovementComp->Velocity.Z = FMath::Max(FallingVelocity, -MaxVelocityToClimbWall);
	MovementComp->UpdateComponentVelocity();
	TransferClimbingWallState();
}

bool UWallClimbingComponent::CanClimbWall() const
{
	return TargetCharacter != nullptr;
}

void UWallClimbingComponent::TransferNotClimbingWallState()
{
	if (bClimbingWall)
	{
		bClimbingWall = false;
		TargetCharacter->GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadiusOnBeginPlay);
		OnCharacterFallOffWall.Broadcast();
	}
}

void UWallClimbingComponent::TransferClimbingWallState()
{
	if (!bClimbingWall)
	{
		bClimbingWall = true;
		TargetCharacter->GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadiusInClimbingWall);
		OnCharacterClimbWall.Broadcast();
	}
}
