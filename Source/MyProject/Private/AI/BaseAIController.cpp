// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Characters/BaseFighter.h"

ABaseAIController::ABaseAIController()
{
	PossessedFighter = nullptr;
	AIInputState = Idle;
}

void ABaseAIController::InitializeController(ABaseFighter* fighter)
{
	PossessedFighter = fighter;

	PC = Cast<APlayerController>(PossessedFighter->GetController());

	SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	PlayerInput = SubSystem->GetPlayerInput();

	RightInput = PossessedFighter->Right;
	LeftInput = PossessedFighter->Left;

	IsFacingRight = PossessedFighter->IsFacingRight();

	GEngine->AddOnScreenDebugMessage(15, 0, FColor::Purple, TEXT("AI initialised"));
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAIController::Tick(float dt)
{
	Super::Tick(dt);

	if (PossessedFighter != nullptr)
	{
		IsFacingRight = PossessedFighter->IsFacingRight();

		/*if (ShouldPress == 0)
			ShouldPress = 1;
		else
		{
			PressForward();

			ShouldPress = 0;
		}*/

		//PressForward();
	}
}

void ABaseAIController::WalkTowardsPlayer()
{

}

void ABaseAIController::WalkAwayFromPlayer()
{

}

void ABaseAIController::AttackPlayer()
{

}

void ABaseAIController::PressForward()
{
	if (PossessedFighter != nullptr)
	{
		if (IsFacingRight)
		{
			FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
			PlayerInput->InjectInputForAction(RightInput, ActionValue);
		}
		else
		{
			FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
			PlayerInput->InjectInputForAction(LeftInput, ActionValue);
		}
	}
}

void ABaseAIController::PressBackward()
{
	if (PossessedFighter != nullptr)
	{
		if (IsFacingRight)
		{
			FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
			PlayerInput->InjectInputForAction(LeftInput, ActionValue);
		}
		else
		{
			FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
			PlayerInput->InjectInputForAction(RightInput, ActionValue);
		}
	}
}

void ABaseAIController::PressForward()
{
	if (PossessedFighter != nullptr)
	{
		FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
		PlayerInput->InjectInputForAction(UpInput, ActionValue);
	}
}

void ABaseAIController::PressBackward()
{
	if (PossessedFighter != nullptr)
	{
		FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
		PlayerInput->InjectInputForAction(DownInput, ActionValue);
	}
}

void ABaseAIController::SwitchInput()
{
	if (PossessedFighter != nullptr)
	{
		if (!IsFacingRight)
		{
			FInputActionValue LeftValue(true); // This can be a bool, float, FVector2D, or FVector
			FInputActionValue RightValue(false); // This can be a bool, float, FVector2D, or FVector
			PlayerInput->InjectInputForAction(LeftInput, LeftValue);
			PlayerInput->InjectInputForAction(RightInput, RightValue);
		}
		else
		{
			FInputActionValue LeftValue(false); // This can be a bool, float, FVector2D, or FVector
			FInputActionValue RightValue(true); // This can be a bool, float, FVector2D, or FVector
			PlayerInput->InjectInputForAction(LeftInput, LeftValue);
			PlayerInput->InjectInputForAction(RightInput, RightValue);
		}
	}
}
