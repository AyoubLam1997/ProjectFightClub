// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomEditors/FighterMovesEditorActor.h"
#include "Characters/BaseStates.h"

TSubclassOf<UGroundedAttackState> AFighterMovesEditorActor::GetState()
{
	return CurrentState;
}
