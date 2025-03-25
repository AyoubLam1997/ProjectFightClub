// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomEditors/MovesEditor.h"
#include "Characters/BaseStates.h"
#include "Components/LightComponent.h"
#include "Engine/StaticMeshActor.h"
#include <Engine/DirectionalLight.h>

void UMovesEditor::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMovesEditor::InitializeViewport(UCanvasPanel* canvas)
{
	View = NewObject<UViewport>(this, UViewport::StaticClass());

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(canvas->AddChild(View));
	slot->SetSize(FVector2D(.5f, .5f));
	slot->SetAnchors(FAnchors(0, 0, .5f, .5f));

	View->SetViewLocation(FVector(-250, 0, -250));

	FVector pos1 = FVector(0, 0, 0);
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
	SpawnInfo.bNoFail = true;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ADirectionalLight* light = View->GetViewportWorld()->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), FVector::Zero(), FRotator(0, -45, 0), SpawnInfo);
	light->GetLightComponent()->SetIntensity(1.f);
	light->GetLightComponent()->SetWorldRotation(FRotator(0, -45.f, 0));

	AStaticMeshActor* actor = View->GetViewportWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	actor->GetStaticMeshComponent()->SetStaticMesh(Skybox);
	actor->GetStaticMeshComponent()->SetWorldScale3D(FVector(100, 100, 100));
	actor->GetStaticMeshComponent()->SetMaterial(0, SkyboxMaterial);
}

void UMovesEditor::GetStateData(TSubclassOf<UFightState> state)
{
	StateToEdit = state;

	SetAnimationData(StateToEdit.GetDefaultObject()->m_AnimationSequence);
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
