// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FixedFrameRateAnimationComponent.generated.h"

class ABaseFighter;

UCLASS(meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UFixedFrameRateAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFixedFrameRateAnimationComponent();

	int CurrentFrame;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int ReturnCurrentFrame();
};
