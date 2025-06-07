// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseAIController.generated.h"

class ABaseFighter;

class AFightingGameMode;

UENUM(BlueprintType)
enum EAIInputState
{
	Idle = 0,
	Walk,
	Block,
	Attack
};

USTRUCT(Blueprintable, BlueprintType)
struct FAICommandAction
{
public:
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, TEnumAsByte<EAIInputState>> InputActionList;

	int CurrentFrame = 0;

	void UpdateAction(ABaseAIController* controller);

	bool IsOnFinalFrame();
};

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

	ABaseAIController();

public:

	virtual void BeginPlay() override;

	virtual void Tick(float dt) override;

	void InitializeController(ABaseFighter* fighter);

	UFUNCTION(BlueprintCallable)
	void WalkTowardsPlayer();
	UFUNCTION(BlueprintCallable)
	void WalkAwayFromPlayer();
	UFUNCTION(BlueprintCallable)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable)
	void PressForward();
	UFUNCTION(BlueprintCallable)
	void PressBackward();
	UFUNCTION(BlueprintCallable)
	void PressUp();
	UFUNCTION(BlueprintCallable)
	void PressDown();
	UFUNCTION(BlueprintCallable)
	void PressLightPunch();
	UFUNCTION(BlueprintCallable)
	void PressLightKick();
	/*UFUNCTION(BlueprintCallable)
	void PressNoButton();*/

	UFUNCTION(BlueprintCallable)
	void SetInputState(EAIInputState InputState);

	UFUNCTION(BlueprintCallable)
	void SetNewCommand(FAICommandAction NewCommand);

	UFUNCTION(BlueprintCallable)
	bool CommandIsFinished();

	/*void PressDownForward();
	void PressDownBackward();
	void PressUpForward();
	void PressUpBackward();*/

	void SwitchInput();

	//void AssignFighterToPossess(ABaseFighter* fighter);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Controller")
	ABaseFighter* PossessedFighter;
	
	UPROPERTY(BlueprintReadOnly)
	AFightingGameMode* FightGameMode;

	EAIInputState AIInputState = EAIInputState::Idle;

	UPROPERTY(BlueprintReadWrite)
	FAICommandAction CurrentCommandAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Controller")
	FAICommandAction IdleCommand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Controller")
	FAICommandAction WalkCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Controller")
	FAICommandAction ComboCommand;

private:

	bool IsFacingRight;

	APlayerController* PC;
	UEnhancedInputLocalPlayerSubsystem* SubSystem;

	UEnhancedPlayerInput* PlayerInput;

	UInputAction* RightInput;
	UInputAction* LeftInput;
	UInputAction* DownRightInput;
	UInputAction* DownLeftInput;
	UInputAction* UpRightInput;
	UInputAction* UpLeftInput;
	UInputAction* UpInput;
	UInputAction* DownInput;
	UInputAction* LightPunchInput;
	UInputAction* MediumPunchInput;
	UInputAction* HeavyPunchInput;
	UInputAction* LightKickInput;
	UInputAction* MediumKickInput;
	UInputAction* HeavyKickInput;

	bool ForwardValue;
	bool BackwardValue;
};
