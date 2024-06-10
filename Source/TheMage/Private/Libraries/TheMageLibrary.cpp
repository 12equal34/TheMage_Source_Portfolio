// By Gyeong-rok Min

#include "Libraries/TheMageLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"

#define THEMAGELIBRARY_SET_COLLISION_DEFINITION( ProfileName ) void UTheMageLibrary::Set##ProfileName##Collision(UPrimitiveComponent* InPrimitiveComponent) { if (InPrimitiveComponent) InPrimitiveComponent->SetCollisionProfileName(TEXT( #ProfileName )); }

namespace TagNames
{
	static const FName Player = TEXT("Player");
	static const FName Monster = TEXT("Monster");
}

void UTheMageLibrary::SetNoCollision(UPrimitiveComponent* InPrimitiveComponent) { if (InPrimitiveComponent) InPrimitiveComponent->SetCollisionProfileName(TEXT("NoCollision")); }
THEMAGELIBRARY_SET_COLLISION_DEFINITION(PlayerPawn);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(MonsterPawn);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(PlayerPawnDetector);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(MonsterPawnDetector);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(PlayerBody);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(MonsterBody);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(PlayerBodyDetector);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(MonsterBodyDetector);
THEMAGELIBRARY_SET_COLLISION_DEFINITION(Item);

FName UTheMageLibrary::GetPlayerTag()
{
	return TagNames::Player;
}

FName UTheMageLibrary::GetMonsterTag()
{
	return TagNames::Monster;
}

bool UTheMageLibrary::HasPlayerTag(AActor* InActor)
{
	return IsValid(InActor) && InActor->ActorHasTag(GetPlayerTag());
}

bool UTheMageLibrary::HasMonsterTag(AActor* InActor)
{
	return IsValid(InActor) && InActor->ActorHasTag(GetMonsterTag());
}

FVector UTheMageLibrary::GetCapsuleBottomApexLocation(UCapsuleComponent* InCapsuleComponent)
{
	FVector Result;
	if (!InCapsuleComponent)
	{
		Result = FVector::ZeroVector;
	}
	else
	{
		const FTransform& CapsuleTransform = InCapsuleComponent->GetComponentTransform();
		const FRotator CapsuleRotator = CapsuleTransform.Rotator();
		const float HalfHeight = InCapsuleComponent->GetScaledCapsuleHalfHeight();

		FVector ToApex;
		if (CapsuleRotator.Pitch == 0.f && CapsuleRotator.Roll == 0.f)
		{
			ToApex = FVector(0.f, 0.f, HalfHeight);
		}
		else
		{
			ToApex = CapsuleTransform.GetUnitAxis(EAxis::Z) * HalfHeight;
		}
		Result = InCapsuleComponent->GetComponentLocation() - ToApex;
	}

	return Result;
}

#undef THEMAGELIBRARY_SET_COLLISION_DEFINITION
