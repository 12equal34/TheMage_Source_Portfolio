#include "Components/PositionGuideComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Libraries/TheMageLibrary.h"

//-----------------------------------------------------------------------------
// FLineTraceToCapsuleBottomInfo
//-----------------------------------------------------------------------------

bool FLineTraceToCapsuleBottomInfo::LineTraceToCapsuleBottom(const UCapsuleComponent* InCapsuleComponent)
{
	check(InCapsuleComponent);
	const bool bIgnoreSelf = true;
	const bool bTraceComplex = false;
	const EDrawDebugTrace::Type DrawDebugType = bDrawDebugTraceForOneFrame ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;

	const UCapsuleComponent* CapsuleComp = InCapsuleComponent;
	const FVector Start = CapsuleComp->GetComponentLocation();
	const FVector End = Start - FVector(0.f, 0.f, MaxTraceReach);

	FHitResult HitResult;
	const bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(CapsuleComp, Start, End, ObjectTypes, bTraceComplex, ActorsToIgnore, DrawDebugType, HitResult, bIgnoreSelf, TraceColor, TraceHitColor);
	if (bHit)
	{
		ReachedPosition = HitResult.ImpactPoint;
		AirHeight = Start.Z - ReachedPosition.Z - CapsuleComp->GetScaledCapsuleHalfHeight();
	}
	return bHit;
}



//-----------------------------------------------------------------------------
// UPositionGuideComponent
//-----------------------------------------------------------------------------

UPositionGuideComponent::UPositionGuideComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);
	SetUsingAbsoluteRotation(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Plane_Ref(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (SM_Plane_Ref.Succeeded())
	{
		SetStaticMesh(SM_Plane_Ref.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI_PositionGuide_Ref(TEXT("/Game/TheMage/Materials/MI_PositionGuide.MI_PositionGuide"));
	if (MI_PositionGuide_Ref.Succeeded())
	{
		SetMaterial(0, MI_PositionGuide_Ref.Object);
	}
	
	UTheMageLibrary::SetNoCollision(this);
}

void UPositionGuideComponent::SetTargetCapsule(UCapsuleComponent* InTargetCapsule)
{
	if (InTargetCapsule != nullptr)
	{
		TargetCapsule = InTargetCapsule;
	}
}

void UPositionGuideComponent::TickComponent(float DeltaTime,ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdatePositionGuide();
}

void UPositionGuideComponent::UpdatePositionGuide()
{
	if (TargetCapsule)
	{
		LineTraceToCapsuleBottom();

		const FVector NewPositionGuideLocation = LineTraceToCapsuleBottomInfo.ReachedPosition + PositionOffset;
		SetWorldLocation(NewPositionGuideLocation);
	}
}

void UPositionGuideComponent::StartUpdatePositionGuide()
{
	if (TargetCapsule)
	{
		SetComponentTickEnabled(true);
	}
}

void UPositionGuideComponent::StopUpdatePositionGuide()
{
	SetComponentTickEnabled(false);
}

float UPositionGuideComponent::CalculateAirHeight()
{
	if (TargetCapsule == nullptr)
	{
		return 0.f;
	}
	
	const bool bShouldUpdateAirHeight = !IsComponentTickEnabled();
	if (bShouldUpdateAirHeight)
	{
		LineTraceToCapsuleBottom();
	}

	return LineTraceToCapsuleBottomInfo.AirHeight;
}

bool UPositionGuideComponent::LineTraceToCapsuleBottom()
{
	return LineTraceToCapsuleBottomInfo.LineTraceToCapsuleBottom(TargetCapsule);
}