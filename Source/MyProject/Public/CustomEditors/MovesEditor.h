// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MovesEditor.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMovesEditor : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	class UFightState* StateToEdit;

	UPROPERTY(BlueprintReadWrite)
	UAnimSequence* AnimationToPlay;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMesh* Mesh;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* MeshComponent;

	int AnimationDuration;
	int StartFrame;
	int EndFrame;
	int CurrentFrame;

	bool bPauseAnimation;

	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GetStateData(class UFightState* state);
	UFUNCTION(BlueprintCallable)
	void SetAnimationData(UAnimSequence* newAnimation);
	void SetMesh(USkeletalMesh* newMesh);
};
