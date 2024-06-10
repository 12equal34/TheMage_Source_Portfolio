#include "Monster/Perception/MonsterSight.h"
#include "Monster/MonsterCharacter.h"
#include "CollisionQueryParams.h"
#include "KismetTraceUtils.h"
#include "DrawDebugHelpers.h"

UMonsterSight::UMonsterSight()
{
}

void UMonsterSight::Init(AMonsterCharacter* InMonsterOwner)
{
	check(InMonsterOwner);
	MonsterOwner = InMonsterOwner;
}

FVector UMonsterSight::GetSightConeOrigin() const
{
	const FVector SightLocation = MonsterOwner->GetActorLocation();
	const FVector SightDirection = MonsterOwner->GetActorForwardVector();
	return FMath::IsNearlyZero(BackwardOffset) ? SightLocation : SightLocation - SightDirection * BackwardOffset;
}

bool UMonsterSight::IsInSightCone(const FVector& TargetLocation)
{
	const FVector Origin = GetSightConeOrigin();
	const FVector Direction = MonsterOwner->GetActorForwardVector();
	const FVector ToTarget = TargetLocation - Origin;
	const FVector::FReal DistToTarget = ToTarget.Size();
	if (DistToTarget <= FarClippingRadius && DistToTarget >= NearClippingRadius)
	{
		// Will return true if squared distance to Target is smaller than SMALL_NUMBER
		if (DistToTarget < KINDA_SMALL_NUMBER)
		{
			return true;
		}

		const FVector NormToTarget = ToTarget / DistToTarget;
		const bool bInSightCone = (Direction | NormToTarget) > FMath::Cos(FMath::DegreesToRadians(PeripheralVisionAngle));

		return bInSightCone;
	}

	return false;
}

bool UMonsterSight::IsVisible(AActor* TargetActor)
{
	if (TargetActor && IsInSightCone(TargetActor->GetActorLocation()))
	{
		if (ComputeVisibility(TargetActor))
		{
			return true;
		}
	}

	return false;
}

bool UMonsterSight::ComputeVisibility(AActor* TargetActor, bool bTraceComplex)
{
	const FVector Start = MonsterOwner->GetActorLocation();
	const FVector End = TargetActor->GetActorLocation();
	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(MonsterLineOfSight), bTraceComplex);
	QueryParams.AddIgnoredActor(MonsterOwner.Get());

	UWorld* World = MonsterOwner->GetWorld();

	FHitResult OutHit;
	const bool bHit = World->LineTraceSingleByChannel(OutHit,Start,End,SightCollisionChannel,QueryParams,FCollisionResponseParams::DefaultResponseParam);

#if WITH_EDITORONLY_DATA && ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		::DrawDebugLineTraceSingle(World, Start, End, EDrawDebugTrace::ForOneFrame, bHit, OutHit, DebugTraceColor, DebugTraceHitColor, 0.f);
	}
#endif

	if (bHit == false)
	{
		return true;
	}

	const AActor* HitResultActor = OutHit.HitObjectHandle.FetchActor();
	return ( HitResultActor ? HitResultActor->IsOwnedBy(TargetActor) : false );
}

#if WITH_EDITORONLY_DATA
void UMonsterSight::DrawDebugSightCone(bool bPersistentLines, float LifeTime)
{
#if ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		UWorld* World = MonsterOwner->GetWorld();
		const FColor Color = DebugSightConeColor.ToFColor(true);
		const FVector Origin = GetSightConeOrigin();
		const FVector Direction = MonsterOwner->GetActorForwardVector();
		const float PeripheralVisionRadians = FMath::DegreesToRadians(PeripheralVisionAngle);
		::DrawDebugCone(World,Origin,Direction,FarClippingRadius,PeripheralVisionRadians,PeripheralVisionRadians, 
						12, Color,bPersistentLines,LifeTime);
		::DrawDebugCircleArc(World, Origin, NearClippingRadius, Direction, PeripheralVisionRadians, 3, Color, bPersistentLines, LifeTime);
		::DrawDebugCircleArc(World, Origin, FarClippingRadius,  Direction, PeripheralVisionRadians, 6, Color, bPersistentLines, LifeTime);
	}
#endif
}
#endif /*WITH_EDITORONLY_DATA*/