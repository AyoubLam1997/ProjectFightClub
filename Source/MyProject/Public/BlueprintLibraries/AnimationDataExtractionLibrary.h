// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnimationDataExtractionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UAnimationDataExtractionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static int ConvertPositionToFrame(float maxDuration);

	UFUNCTION(BlueprintCallable)
	static int ConvertStringToInt(FString textToInt);

	UFUNCTION(BlueprintCallable)
	static float ConvertStringToFloat(FString textToFloat);

	UFUNCTION(BlueprintCallable)
	static void UpdateProperty(UObject* object, const FName& name, int value);

	UFUNCTION(BlueprintCallable)
	static void UpdateFloatProperty(UObject* object, const FName& name, float value);

	UFUNCTION(BlueprintCallable)
	static void UpdateVectorProperty(UObject* object, const FName& name, FVector value);
};
