// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraRestrictorInterface.generated.h"

class ACameraRestrictor;

UINTERFACE(MinimalAPI, Blueprintable)
class UCameraRestrictorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* 
*/
class THEMAGE_API ICameraRestrictorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="CameraRestrictorInterface")
	void SetOverlappingCameraRestrictor(ACameraRestrictor* InCameraRestrictor);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="CameraRestrictorInterface")
	ACameraRestrictor* GetOverlappingCameraRestrictor() const;

};
