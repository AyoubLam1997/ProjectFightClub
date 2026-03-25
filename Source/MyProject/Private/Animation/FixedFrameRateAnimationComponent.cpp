// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FixedFrameRateAnimationComponent.h"

#include "Characters/BaseFighter.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimSingleNodeInstance.h"

// Sets default values for this component's properties
UFixedFrameRateAnimationComponent::UFixedFrameRateAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFixedFrameRateAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	/*ACharacter* figher = Cast<ABaseFighter>(GetOwner());
	 
	figher->GetMesh()->SetPlayRate(0);*/

	//CurrentFrame = 0;

	// ...
	
}

// Called every frame
void UFixedFrameRateAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*float d = DeltaTime;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(d));

	ACharacter* figher = Cast<ABaseFighter>(GetOwner());

	figher->GetMesh()->SetPlayRate(1);
	figher->GetMesh()->Play(1);*/

	/*ACharacter* fighter = Cast<ABaseFighter>(GetOwner());

	UAnimSingleNodeInstance* SingleNodeInstance = fighter->GetMesh()->GetSingleNodeInstance();

	if (SingleNodeInstance->GetAnimationAsset() == nullptr)
		return;

	CurrentFrame = (int)(fighter->GetMesh()->GetPosition() * 60);

	int MaxFrame = (int)(SingleNodeInstance->GetAnimationAsset()->GetPlayLength() * 60);

	CurrentFrame += 1;

	if(CurrentFrame > MaxFrame)
	{
		CurrentFrame = 0;
	}

	float p = float((float(CurrentFrame) / 60.f));

	fighter->GetMesh()->SetPosition(p);*/

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(CurrentFrame));

	//figher->GetMesh()->SetPosition(figher->GetMesh()->GetPosition() + DeltaTime);

	// ...
}

int UFixedFrameRateAnimationComponent::ReturnCurrentFrame()
{
	return CurrentFrame;
}

// This whole sectiom is for 
//void UFixedFrameRateAnimationComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	ACharacter* figher = Cast<ACharacter>(GetOwner());
//
//	figher->GetMesh()->SetPlayRate(0);
//
//	// ...
//
//}
//
//
//// Called every frame
//void UFixedFrameRateAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	ACharacter* fighter = Cast<ACharacter>(GetOwner());
//
//	UAnimInstance* anim = fighter->GetMesh()->GetAnimInstance();
//
//	if (anim == nullptr)
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Does not exist");
//
//		return;
//	}
//
//	UAnimMontage* Montage = anim->GetCurrentActiveMontage();
//
//	if (Montage == nullptr)
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Montage does not exist");
//
//		return;
//	}
//
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Montage does exist");
//
//	//UAnimSingleNodeInstance* SingleNodeInstance = fighter->GetMesh()->GetSingleNodeInstance();
//
//	//if (SingleNodeInstance->GetAnimationAsset() == nullptr)
//	//{
//	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Does not exist");
//
//	//	return;
//	//}
//
//	anim->Montage_GetPosition(Montage);
//
//	int CurrentFrame = (int)(anim->Montage_GetPosition(Montage) * 60);
//
//	int MaxFrame = (int)(Montage->GetPlayLength() * 60);
//
//	CurrentFrame += 1;
//
//	if (CurrentFrame > MaxFrame)
//	{
//		CurrentFrame = 0;
//	}
//
//	float p = float((float(CurrentFrame) / 60.f));
//
//	anim->Montage_SetPosition(Montage, p);
//
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(CurrentFrame));
//
//	/*int CurrentFrame = (int)(fighter->GetMesh()->GetPosition() * 60);
//
//	int MaxFrame = (int)(Montage->GetPlayLength() * 60);
//
//	CurrentFrame += 1;
//
//	if(CurrentFrame > MaxFrame)
//	{
//		CurrentFrame = 0;
//	}
//
//	float p = float((float(CurrentFrame) / 60.f));
//
//	fighter->GetMesh()->SetPosition(p);*/
//
//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(MaxFrame));
//
//	//figher->GetMesh()->SetPosition(figher->GetMesh()->GetPosition() + DeltaTime);
//
//	// ...
//}
