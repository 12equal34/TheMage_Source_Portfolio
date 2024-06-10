#include "Characters/BasePlayerCharacter.h"
#include "Components/HPComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WallClimbingComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Libraries/TheMageLibrary.h"
#include "Inventory/InventoryComponent.h"
#include "PaperFlipbookComponent.h"



ABasePlayerCharacter::ABasePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	UTheMageLibrary::SetPlayerBodyCollision(GetSprite());
	UTheMageLibrary::SetPlayerPawnCollision(GetCapsuleComponent());
	UTheMageLibrary::SetMonsterPawnDetectorCollision(GetConnector());

	GetSprite()->SetGenerateOverlapEvents(true);

	Tags.Add(UTheMageLibrary::GetPlayerTag());

	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	CharMovement->GravityScale = 6.f;
	CharMovement->SetCrouchedHalfHeight(58.f);
	CharMovement->MaxWalkSpeed = 800.f;
	CharMovement->MaxWalkSpeedCrouched = 400.f;
	CharMovement->bUseFlatBaseForFloorChecks = true;
	CharMovement->JumpZVelocity = 800.f;
	CharMovement->AirControl = 1.f;
	CharMovement->FallingLateralFriction = 10.f;
	CharMovement->GetNavAgentPropertiesRef().bCanCrouch = true;
	CharMovement->bCanWalkOffLedgesWhenCrouching = true;

	bUseControllerRotationYaw = false;
	JumpMaxHoldTime = 0.2f;
	JumpMaxCount = 2;

	/**
	* Create Default Subobjects.
	*/
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteLocation(true);
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->SetWorldRotation(FRotator(-35.f, -90.f, 0.f));
	SpringArmComponent->TargetArmLength = 800.f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw   = false;
	SpringArmComponent->bInheritRoll  = false;
	SpringArmComponent->ComponentTags.Add(TEXT("CameraArm"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	check(CameraComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);
	CameraComponent->SetFieldOfView(70.f);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	WallClimbingComponent = CreateDefaultSubobject<UWallClimbingComponent>(TEXT("WallClimbingComponent"));
}

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	WallClimbingComponent->OnCharacterClimbWall.AddDynamic(this, &ABasePlayerCharacter::OnClimbWall);
	WallClimbingComponent->OnCharacterFallOffWall.AddDynamic(this, &ABasePlayerCharacter::OnFallOffWall);
}

void ABasePlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (WallClimbingComponent->CanClimbWall())
	{
		WallClimbingComponent->TryClimbWall(MoveInput);
	}
}

bool ABasePlayerCharacter::CanMove_Implementation() const
{
	return Super::CanMove_Implementation() && !WallClimbingComponent->IsClimbingWall();
}

bool ABasePlayerCharacter::CanCrouch() const
{
	return Super::CanCrouch();
}

void ABasePlayerCharacter::OnClimbWall()
{
	SetReverseFace(true);
	UpdateSpriteRotation();
}

void ABasePlayerCharacter::OnFallOffWall()
{
	SetReverseFace(false);
	UpdateSpriteRotation();
}

void ABasePlayerCharacter::SetInvincible(bool bNewInvincible)
{
	if (bInvincible != bNewInvincible)
	{
		bInvincible = bNewInvincible;
		if (bInvincible)
		{
			UTheMageLibrary::SetNoCollision(GetSprite());
		}
		else
		{
			UTheMageLibrary::SetPlayerBodyCollision(GetSprite());
		}
	}
}