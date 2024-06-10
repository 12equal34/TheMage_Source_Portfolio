// By Gyeong-rok Min

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TheMageLibrary.generated.h"

/**
 * 
 */
UCLASS()
class THEMAGE_API UTheMageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Tag")
	static FName GetPlayerTag();

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Tag")
	static FName GetMonsterTag();

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Tag")
	static bool HasPlayerTag(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Tag")
	static bool HasMonsterTag(AActor* InActor);

public:
	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetNoCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetPlayerPawnCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetMonsterPawnCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetPlayerPawnDetectorCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetMonsterPawnDetectorCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetPlayerBodyCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetMonsterBodyCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetPlayerBodyDetectorCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetMonsterBodyDetectorCollision(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Collision")
	static void SetItemCollision(UPrimitiveComponent* InPrimitiveComponent);

public:
	UFUNCTION(BlueprintCallable, Category="TheMageLibrary|Primitive")
	static FVector GetCapsuleBottomApexLocation(UCapsuleComponent* InCapsuleComponent);
};
