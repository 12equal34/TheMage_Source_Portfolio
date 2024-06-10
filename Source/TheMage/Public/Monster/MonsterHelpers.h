#pragma once

#include "CoreMinimal.h"
#include "Math/MathFwd.h"

namespace UE::MonsterHelpers
{
	namespace SentinelValue
	{
		inline static const FVector InvalidLocation = FVector(FLT_MAX);
	}
	

	THEMAGE_API FVector FindClosestLocation(const FVector& Origin, const TArray<FVector>& Locations);

	THEMAGE_API AActor* FindClosestActor(const FVector& Origin, const TArray<AActor*>& TargetActors);

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
	THEMAGE_API bool CheckIsTargetInSightCone(const FVector& StartLocation, const FVector& ConeDirectionNormal, float PeripheralVisionAngleCos,
									          float ConeDirectionBackwardOffset, float NearClippingRadiusSq, float FarClippingRadiusSq, const FVector& TargetLocation);
}
