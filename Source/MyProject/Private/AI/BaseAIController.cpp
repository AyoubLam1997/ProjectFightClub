// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Characters/BaseFighter.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/FightingGameMode.h"

void FAICommandAction::UpdateAction(ABaseAIController* controller)
{
	CurrentFrame += 1;

	if(InputActionList.Contains(CurrentFrame))
		controller->SetInputState(InputActionList[CurrentFrame]);
}

bool FAICommandAction::IsOnFinalFrame() const
{
	return CurrentFrame >= MaxFrame;
}

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
	LightPunchInput = PossessedFighter->LightPunch;
	LightKickInput = PossessedFighter->LightKick;
	UpInput = PossessedFighter->Up;

	IsFacingRight = PossessedFighter->IsFacingRight();

	GEngine->AddOnScreenDebugMessage(15, 0, FColor::Purple, TEXT("AI initialised"));
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	FightGameMode = Cast<AFightingGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ABaseAIController::Tick(float dt)
{
	Super::Tick(dt);

	CurrentCommandAction.UpdateAction(this);

	if (PossessedFighter != nullptr)
	{
		IsFacingRight = PossessedFighter->IsFacingRight();

		switch(AIInputState)
		{
		case Idle:
			break;

		case Walk:
		{
			PressForward();
		}
		break;
		case Block:
		{
			PressBackward();
		}
		break;
		case Attack:
		{
			PressLightPunch();
		}
		case Jump:
		{
			PressUp();
		}
		break;

		default:
			break;
		}
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

void ABaseAIController::PressUp()
{
	if (PossessedFighter != nullptr)
	{
		FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
		PlayerInput->InjectInputForAction(UpInput, ActionValue);
	}
}

void ABaseAIController::PressDown()
{
	if (PossessedFighter != nullptr)
	{
		//FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
		//PlayerInput->InjectInputForAction(DownInput, ActionValue);
	}
}

void ABaseAIController::PressLightPunch()
{
	if (PossessedFighter != nullptr)
	{
		FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
		PlayerInput->InjectInputForAction(LightPunchInput, ActionValue);
	}
}

void ABaseAIController::PressLightKick()
{
	if (PossessedFighter != nullptr)
	{
		FInputActionValue ActionValue(true); // This can be a bool, float, FVector2D, or FVector
		PlayerInput->InjectInputForAction(LightKickInput, ActionValue);
	}
}

void ABaseAIController::SetInputState(EAIInputState InputState)
{
	AIInputState = InputState;
}

void ABaseAIController::SetNewCommand(FAICommandAction NewCommand)
{
	CurrentCommandAction = NewCommand;

	CurrentCommandAction.CurrentFrame = 0;
}


bool ABaseAIController::CommandIsFinished()
{
	return CurrentCommandAction.IsOnFinalFrame();
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
