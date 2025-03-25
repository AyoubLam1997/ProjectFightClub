// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Components/Viewport.h"
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include "MovesEditor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UMovesEditor : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UFightState> StateToEdit;

	UPROPERTY(BlueprintReadWrite)
	UAnimSequence* AnimationToPlay;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMesh* Mesh;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite)
	int AnimationDuration;
	UPROPERTY(BlueprintReadWrite)
	int StartActiveFrame;
	UPROPERTY(BlueprintReadWrite)
	int EndActiveFrame;
	UPROPERTY(BlueprintReadWrite)
	int RecoveryFrames;
	UPROPERTY(BlueprintReadWrite)
	int CurrentFrame;

	UPROPERTY(BlueprintReadWrite)
	bool bPauseAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Skybox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* SkyboxMaterial;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UViewport> View;
	
	virtual void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitializeViewport(UCanvasPanel* canvas);

	UFUNCTION(BlueprintCallable)
	void GetStateData(TSubclassOf<UFightState> state);
	UFUNCTION(BlueprintCallable)
	void SetAnimationData(UAnimSequence* newAnimation);
	UFUNCTION(BlueprintCallable)
	void SetMesh(USkeletalMesh* newMesh);
};
