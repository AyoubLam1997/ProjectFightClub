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
	
};
