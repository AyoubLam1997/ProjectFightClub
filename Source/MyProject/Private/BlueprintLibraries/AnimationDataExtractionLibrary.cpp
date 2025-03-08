// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibraries/AnimationDataExtractionLibrary.h"

int UAnimationDataExtractionLibrary::ConvertPositionToFrame(float maxDuration)
{
	if (maxDuration > 0.f)
	{
		return (int)(maxDuration * 60);
	}

	return 0;
}

int UAnimationDataExtractionLibrary::ConvertStringToInt(FString textToInt)
{
	char* result = TCHAR_TO_ANSI(*textToInt);

	int value = atoi(result);

	if (value > 0)
		return value;

	return 0;
}
