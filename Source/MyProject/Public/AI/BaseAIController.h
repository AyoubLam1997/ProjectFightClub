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

	void PressForward();
	void PressBackward();
	void PressUp();
	void PressDown();
	/*void PressDownForward();
	void PressDownBackward();
	void PressUpForward();
	void PressUpBackward();*/

	void SwitchInput();

	//void AssignFighterToPossess(ABaseFighter* fighter);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Controller")
	ABaseFighter* PossessedFighter;
	
	EAIInputState AIInputState;

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
};
