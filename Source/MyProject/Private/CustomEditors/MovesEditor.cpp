// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomEditors/MovesEditor.h"
#include "Characters/BaseStates.h"

void UMovesEditor::NativeConstruct()
{

}

void UMovesEditor::GetStateData(UFightState* state)
{
	StateToEdit = state;

	SetAnimationData(StateToEdit->m_AnimationSequence);
}

void UMovesEditor::SetAnimationData(UAnimSequence* newAnimation)
{
	AnimationToPlay = newAnimation;

	Mesh = AnimationToPlay->GetPreviewMesh();

	MeshComponent->PlayAnimation(AnimationToPlay, 1.f);

	CurrentFrame = 1;
	AnimationDuration = (int)(AnimationToPlay->GetPlayLength() * 60);
}

void UMovesEditor::SetMesh(USkeletalMesh* newMesh)
{
	Mesh = newMesh;
}

void UMovesEditor::NativeTick(const FGeometry& MyGeometry, float deltaTime)
{
	Super::NativeTick(MyGeometry, deltaTime);

	if (StateToEdit == nullptr || Mesh == nullptr || MeshComponent == nullptr)
		return;

	CurrentFrame = (int)(MeshComponent->GetPosition() * 60);

	bPauseAnimation = 1;

	if (!bPauseAnimation)
	{
		MeshComponent->PlayAnimation(AnimationToPlay, 1.f);
	}
	else
		MeshComponent->Stop();
}
