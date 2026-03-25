// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomEditors/MovesEditor.h"
#include "Characters/BaseStates.h"
#include "Components/LightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "CustomEditors/FighterMovesEditorActor.h"
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

	EditorActor = View->GetViewportWorld()->SpawnActor<AFighterMovesEditorActor>(AFighterMovesEditorActor::StaticClass());

	ADirectionalLight* light = View->GetViewportWorld()->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), FVector::Zero(), FRotator(0, -45, 0), SpawnInfo);
	light->GetLightComponent()->SetIntensity(1.f);
	light->GetLightComponent()->SetWorldRotation(FRotator(0, -45.f, 0));

	AStaticMeshActor* actor = View->GetViewportWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	actor->GetStaticMeshComponent()->SetStaticMesh(Skybox);
	actor->GetStaticMeshComponent()->SetWorldScale3D(FVector(100, 100, 100));
	actor->GetStaticMeshComponent()->SetMaterial(0, SkyboxMaterial);

	FVector actorPos = EditorActor->GetActorLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(View->GetViewLocation(), actorPos);
	View->SetViewRotation(lookAtRotation);
}

void UMovesEditor::GetStateData(TSubclassOf<UFightState> state)
{
	StateToEdit = state;

	SetMesh(StateToEdit.GetDefaultObject()->AnimationSequenceToPlay->GetPreviewMesh());
	SetAnimationData(StateToEdit.GetDefaultObject()->AnimationSequenceToPlay);
}

void UMovesEditor::SetAnimationData(UAnimSequence* newAnimation)
{
	CurrentSelectedAnimation = newAnimation;
	EditorActor->GetSkeletalMeshComponent()->PlayAnimation(CurrentSelectedAnimation, 1);

	CurrentFrame = 1;
	AnimationDuration = (int)(EditorActor->GetSkeletalMeshComponent()->GetPosition() * 60);
}

void UMovesEditor::SetMesh(USkeletalMesh* newMesh)
{
	EditorActor->GetSkeletalMeshComponent()->SetSkeletalMesh(newMesh);
}

void UMovesEditor::SetSelectedFightState(UObject* yourObj, FName name)
{
	//int32 value;
	//if (UKismetSystemLibrary::GetEditorProperty(EditorActor, name, value))
	//{
	//	/*if (UKismetSystemLibrary::SetEditorProperty(EditorActor, name, value, EPropertyAccessChangeNotifyMode::Default))
	//	{
	//		GetStateData(EditorActor->CurrentState);
	//	}*/
	//}

	FProperty* prop = yourObj->GetClass()->FindPropertyByName("CurrentState");
	if (prop != nullptr)
	{
		if (FObjectProperty* objPtrProp = CastField<FObjectProperty>(prop))
		{
			if (UObject* desiredValue = objPtrProp->GetPropertyValue(prop))
			{
				/*if (desiredValue != nullptr)
				{
					UFightState* state = Cast<UFightState>(desiredValue);

					EditorActor->CurrentState = state->StaticClass();

					if (EditorActor->CurrentState)
						GetStateData(EditorActor->CurrentState);
				}*/

				/*objPtrProp->SetObjectPropertyValue_InContainer(EditorActor, desiredValue);*/

				//if (UKismetSystemLibrary::Generic_GetEditorProperty(EditorActor, prop, desiredValue, objPtrProp))
				//{
				//	//if (UKismetSystemLibrary::Generic_SetEditorProperty(EditorActor, prop, desiredValue, objPtrProp, EPropertyAccessChangeNotifyMode::Default))
				//	//{
				//	//	//GetStateData(EditorActor->CurrentState);
				//	//}
				//	//else
				//	//{
				//	//	UE_LOG(LogTemp, Warning, TEXT("Could not set editor property."));
				//	//}
				//}
				//else
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("Could not get editor property."));
				//}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to cast to object ptr property"));
			}
		}
	}
}

void UMovesEditor::NativeTick(const FGeometry& MyGeometry, float deltaTime)
{
	Super::NativeTick(MyGeometry, deltaTime);

	if (StateToEdit == nullptr || EditorActor->GetSkeletalMeshComponent() == nullptr || CurrentSelectedAnimation == nullptr)
		return;

	CurrentFrame = (int)(EditorActor->GetSkeletalMeshComponent()->GetPosition() * 60);

	bPauseAnimation = 1;

	if (!bPauseAnimation)
	{
		EditorActor->GetSkeletalMeshComponent()->PlayAnimation(CurrentSelectedAnimation, 1);
	}
	else
		EditorActor->GetSkeletalMeshComponent()->Stop();
}
