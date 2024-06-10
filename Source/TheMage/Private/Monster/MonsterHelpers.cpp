#include "Monster/MonsterHelpers.h"
#include "GameFramework/Actor.h"


namespace UE::MonsterHelpers
{
	FVector FindClosestLocation(const FVector& Origin, const TArray<FVector>& Locations)
	{
		FVector BestLocation = SentinelValue::InvalidLocation;
		FVector::FReal BestDistanceSq = TNumericLimits<FVector::FReal>::Max();

		for (const FVector& Candidate : Locations)
		{
			const FVector::FReal CurrentDistanceSq = FVector::DistSquared(Origin, Candidate);
			if (CurrentDistanceSq < BestDistanceSq)
			{
				BestDistanceSq = CurrentDistanceSq;
				BestLocation = Candidate;
			}
		}

		return BestLocation;
	}

	AActor* FindClosestActor(const FVector& Origin,const TArray<AActor*>& TargetActors)
	{
		if (TargetActors.Num() == 0)      return nullptr;
		else if (TargetActors.Num() == 1) return TargetActors[0];

		AActor* ClosestTarget = TargetActors[0];
		float ClosestDistSq = FVector::DistSquared(Origin, ClosestTarget->GetActorLocation());

		for (int32 i = 1; i < TargetActors.Num(); ++i)
		{
			const FVector::FReal DistSq = FVector::DistSquared(Origin, TargetActors[i]->GetActorLocation());
			if (DistSq < ClosestDistSq)
			{
				ClosestDistSq = DistSq;
				ClosestTarget = TargetActors[i];
			}
		}

		return ClosestTarget;
	}

	//----------------------------------------------------------------------//
	// CheckIsTargetInSightCone
	//                     F
	//                   *****  
	//              *             *
	//          *                     *
	//       *                           *
	//     *                               *
	//   *                                   * 
	//    \                                 /
	//     \                               /
	//      \                             /
	//       \             X             /
	//        \                         /
	//         \          ***          /
	//          \     *    N    *     /
	//           \ *               * /
	//            N                 N
	//            
	//           
	//           
	//           
	//
	// 
	//                     B 
	//
	// X = StartLocation
	// B = Backward offset
	// N = Near Clipping Radius (from the StartLocation adjusted by Backward offset)
	// F = Far Clipping Radius (from the StartLocation adjusted by Backward offset)
	//----------------------------------------------------------------------//
	bool CheckIsTargetInSightCone(const FVector& StartLocation, const FVector& ConeDirectionNormal, float PeripheralVisionAngleCos,
								  float ConeDirectionBackwardOffset, float NearClippingRadiusSq, float FarClippingRadiusSq, const FVector& TargetLocation)
	{
		const FVector BaseLocation = FMath::IsNearlyZero(ConeDirectionBackwardOffset) ? StartLocation : StartLocation - ConeDirectionNormal * ConeDirectionBackwardOffset;
		const FVector ActorToTarget = TargetLocation - BaseLocation;
		const FVector::FReal DistToTargetSq = ActorToTarget.SizeSquared();
		if (DistToTargetSq <= FarClippingRadiusSq && DistToTargetSq >= NearClippingRadiusSq)
		{
			// Will return true if squared distance to Target is smaller than SMALL_NUMBER
			if (DistToTargetSq < SMALL_NUMBER)
			{
				return true;
			}

			// Calculate the normal here instead of calling GetUnsafeNormal as we already have the DistToTargetSq (optim)
			const FVector DirectionToTargetNormal = ActorToTarget * FMath::InvSqrt(DistToTargetSq);

			return FVector::DotProduct(DirectionToTargetNormal, ConeDirectionNormal) > PeripheralVisionAngleCos;
		}

		return false;
	}
}