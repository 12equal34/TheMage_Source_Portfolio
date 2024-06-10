// This game is making by Gyeong-rok Min.

#include "Controllers/MagePlayerController.h"
#include "Camera/CameraActor.h"
#include "LevelActors/CameraRestrictor.h"
#include "Characters/BasePlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"

AMagePlayerController::AMagePlayerController()
{
	
}

void AMagePlayerController::SpawnCamera(const FTransform& SpawnTransform,float InLifeSpan)
{
	/*ACameraActor* Camera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), SpawnTransform);
	Camera->GetCameraComponent()->SetAspectRatio(CameraComponent->AspectRatio);
	Camera->GetCameraComponent()->SetFieldOfView(CameraComponent->FieldOfView);
	Camera->GetCameraComponent()->bConstrainAspectRatio = false;
	Camera->SetLifeSpan(InLifeSpan);
	PlayerCameraManager->SetViewTarget(Camera);*/
}

void AMagePlayerController::FadeOutCamera()
{
	PlayerCameraManager->StartCameraFade(0.f, 1.f, FadeOutDuration, CameraFadeColor, false, true);
}

void AMagePlayerController::FadeInCamera()
{
	PlayerCameraManager->StartCameraFade(1.f, 0.f, FadeInDuration, CameraFadeColor, false, true);
}

void AMagePlayerController::SetOverlappingCameraRestrictor_Implementation(ACameraRestrictor* InCameraRestrictor)
{
	OverlappingCameraRestrictor = InCameraRestrictor;
}

ACameraRestrictor* AMagePlayerController::GetOverlappingCameraRestrictor_Implementation() const
{
	return OverlappingCameraRestrictor;
}

void AMagePlayerController::UpdateCameraPosition(float DeltaTime)
{
	if (!IsValid(ControlledCharacter) || !IsValid(ControlledCharCameraArm))
	{
		return;
	}

	// Interlerp the camera position from current to target.
	const FVector Current = ControlledCharCameraArm->GetComponentLocation();
	FVector Target;
	if (OverlappingCameraRestrictor)
	{
		Target = OverlappingCameraRestrictor->GetCamreaPosition();
	}
	else
	{
		Target = ControlledCharacter->GetActorLocation() + CameraOffset;
	}
	FVector CameraPosition = FMath::VInterpTo(Current, Target, DeltaTime, CameraInterpSpeed);
	ControlledCharCameraArm->SetWorldLocation(CameraPosition);
}

void AMagePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	ControlledCharacter = Cast<ABasePlayerCharacter>(InPawn);
	if (ControlledCharacter)
	{
		USpringArmComponent* FoundSpringArm = ControlledCharacter->GetComponentByClass<USpringArmComponent>();
		if (FoundSpringArm && FoundSpringArm->ComponentHasTag(TEXT("CameraArm")))
		{
			ControlledCharCameraArm = FoundSpringArm;
		}
	}
}

void AMagePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
