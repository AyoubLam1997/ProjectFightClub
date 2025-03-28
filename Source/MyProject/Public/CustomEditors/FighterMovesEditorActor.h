// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "FighterMovesEditorActor.generated.h"

/**
 * 
 */

class UGroundedAttackState;

UCLASS()
class MYPROJECT_API AFighterMovesEditorActor : public ASkeletalMeshActor
{
	GENERATED_BODY()
	
public:

	TSubclassOf<UGroundedAttackState> GetState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGroundedAttackState> CurrentState;
};
