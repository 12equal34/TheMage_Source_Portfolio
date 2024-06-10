// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HPInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHPInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEMAGE_API IHPInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float Injure(float InDamage, AActor* InInstigator = nullptr) = 0;
	virtual float GetHP() const = 0;
};
