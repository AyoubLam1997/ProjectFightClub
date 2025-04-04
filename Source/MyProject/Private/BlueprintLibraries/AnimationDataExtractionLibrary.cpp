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

float UAnimationDataExtractionLibrary::ConvertStringToFloat(FString textToFloat)
{
	float value = FCString::Atof(*textToFloat);

	if (value > 0.f)
		return value;

	return 0.f;
}

void UAnimationDataExtractionLibrary::UpdateProperty(UObject* object, const FName& name, int value)
{
	if (object)
	{
		if (const UClass* Class = object->GetClass())
		{
			if (UObject* default = Class->GetDefaultObject())
			{
				FIntProperty* prop = CastField<FIntProperty>(Class->FindPropertyByName(name));
				prop->SetPropertyValue_InContainer(default, value);
			}
		}
	}
}


void UAnimationDataExtractionLibrary::UpdateFloatProperty(UObject* object, const FName& name, float value)
{
	if (object)
	{
		if (const UClass* Class = object->GetClass())
		{
			if (UObject* default = Class->GetDefaultObject())
			{
				FFloatProperty* prop = CastField<FFloatProperty>(Class->FindPropertyByName(name));
				prop->SetPropertyValue_InContainer(default, value);
			}
		}
	}
}


void UAnimationDataExtractionLibrary::UpdateVectorProperty(UObject* object, const FName& name, FVector value)
{
	if (object)
	{
		if (const UClass* Class = object->GetClass())
		{
			if (UObject* default = Class->GetDefaultObject())
			{
				if(FProperty* prop = Class->FindPropertyByName(name))
				{
					if(FVector* vect = prop->ContainerPtrToValuePtr<FVector>(default))
					{
						vect->Set(value.X, value.Y, value.Z);
					}
				}
			}
		}
	}
}