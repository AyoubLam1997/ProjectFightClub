// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "InputBuffer.h"

#include "BaseStates.generated.h"

class ABaseFighter;
class UHitboxResponder;
enum class EInputType;

/**
 * 
 */

//UINTERFACE(MinimalAPI, Blueprintable)
//class UFightState : public UInterface
//{
//	GENERATED_BODY()
//};

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UFightState : public UObject
{
	GENERATED_BODY()
public:

	//UFightState* NextState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* AnimationSequenceToPlay;

	virtual void Enter(ABaseFighter& fighter) {};
	virtual UFightState* HandleInput(ABaseFighter& fighter) { return nullptr; };
	virtual void Update(ABaseFighter& fighter) {};
	virtual void Exit(ABaseFighter& fighter) {};
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UGroundedState : public UFightState
{
	GENERATED_BODY()
public:
	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UCrouchState : public UGroundedState
{
	GENERATED_BODY()
public:
	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API ULayingState : public UGroundedState
{
	GENERATED_BODY()
public:

	ULayingState();
	ULayingState(float duration);

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:

	float LayingTimer;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UStandingUpState : public UGroundedState
{
	GENERATED_BODY()
public:

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UForwardWalkState : public UGroundedState
{
	GENERATED_BODY()
public:
	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UBackwardWalkState : public UGroundedState
{
	GENERATED_BODY()
public:
	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UDash : public UGroundedState
{
	GENERATED_BODY()

public:

	//Dash();
	//Dash(FVector impulse);

	virtual void Enter(ABaseFighter& fighter) override {};
	virtual UFightState* HandleInput(ABaseFighter& fighter) override { return nullptr; };
	virtual void Update(ABaseFighter& fighter) override {};
	virtual void Exit(ABaseFighter& fighter) override {};

	UPROPERTY(EditAnywhere)
	FVector DashImpulse;

	UPROPERTY(EditAnywhere)
	int DashStartUp;
	UPROPERTY(EditAnywhere)
	int DashStartRecovery;

	int CurrentFrame;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UForwardDash : public UDash
{
	GENERATED_BODY()

public:

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

//UCLASS(Blueprintable, BlueprintType)
//class MYPROJECT_API UBackwardDash : public UPrimaryDataAsset, public Dash
//{
//	GENERATED_BODY()
//
//public:
//
//	virtual void Enter(ABaseFighter& fighter) override;
//	virtual FightState* HandleInput(ABaseFighter& fighter) override;
//	virtual void Update(ABaseFighter& fighter) override;
//	virtual void Exit(ABaseFighter& fighter) override;
//};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UAirborneState : public UFightState
{
	GENERATED_BODY()
public:

	float CurrentFallVelocity;
	float MaxFallVelocity = 1500.f;

	UAirborneState();
	UAirborneState(FVector impulse);
	UAirborneState(float velocity);

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:

	FVector ImpulseDirection;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UNeutralJumpState : public UAirborneState
{
	GENERATED_BODY()
public:

	UNeutralJumpState() {};

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UForwardJumpState : public UAirborneState
{
	GENERATED_BODY()
public:

	float ForwardVelocity = 400.f;

	UForwardJumpState();
	UForwardJumpState(FVector impulse);
	UForwardJumpState(float velocity);

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:

	FVector ImpulseDirection;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UBackwardJumpState :public UAirborneState
{
	GENERATED_BODY()
public:

	float BackwardVelocity = -400.f;

	UBackwardJumpState();
	UBackwardJumpState(FVector impulse);
	UBackwardJumpState(float velocity);

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:

	FVector ImpulseDirection;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UBlockState : public UFightState
{
	GENERATED_BODY()
public:

	UBlockState() {};

	int CurrentStunTime;

	virtual void Enter(ABaseFighter& fighter) override {};
	virtual UFightState* HandleInput(ABaseFighter& fighter) override { return nullptr; };
	virtual void Update(ABaseFighter& fighter) override {};
	virtual void Exit(ABaseFighter& fighter) override {};

private:
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UBlockStunState : public UBlockState
{
	GENERATED_BODY()
public:

	UBlockStunState() {};
	UBlockStunState(int duration, float velocity);

	void Init(int duration, float velocity);

	float Pushback;
	int StunDuration;

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UStunState : public UFightState
{
	GENERATED_BODY()
public:

	int CurrentStunTime;

	UStunState() {};

	virtual void Enter(ABaseFighter& fighter) override {};
	virtual UFightState* HandleInput(ABaseFighter& fighter) override { return nullptr; };
	virtual void Update(ABaseFighter& fighter) override {};
	virtual void Exit(ABaseFighter& fighter) override {};

private:
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UKnockbackStunState : public UStunState
{
	GENERATED_BODY()
public:

	float Pushback;
	int StunDuration;

	UKnockbackStunState();
	UKnockbackStunState(float pushback, int duration);

	void Init(float pushback, int duration);

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UAirStunState : public UStunState
{
	GENERATED_BODY()
public:

	float VerticalKnockBack;
	float HorizontalKnockback;

	float MaxFallVelocity;
	float CurrentFallVelocity;

	UAirStunState();
	UAirStunState(float velocity, float horizontal);

	void Init(float velocity, float horizontal);

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:

	FVector ImpulseDirection;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UGrabStartupState : public UFightState
{
	GENERATED_BODY()
public:

	UGrabStartupState();

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

private:

	int CurrentFrame;

	int MinFrame = 5;
	int MaxFrame = 8;
};

// DEV NOTE: Probably make this a uclass that designers can edit
//class MYPROJECT_API GrabbedState : public FightState
//{
//public:
//
//	GrabbedState();
//
//	virtual void Enter(ABaseFighter& fighter) override;
//	virtual FightState* HandleInput(ABaseFighter& fighter) override;
//	virtual void Update(ABaseFighter& fighter) override;
//	virtual void Exit(ABaseFighter& fighter) override;
//
//private:
//};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UGrabState : public UFightState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	int DamageFrame;

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

	UFUNCTION(BlueprintCallable)
	void SetEnemy(ABaseFighter* fighter);

private:

	ABaseFighter* EnemyFighter;
};

// TODO: Remove GroundedState property
UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UGroundedAttackState : public UGroundedState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float KnockBack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int StunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinFrame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxFrame;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int FreezeTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector BoxPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector BoxExtent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BlockKnockBack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BlockStunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* TempAnimSeq;

	UPROPERTY(EditAnywhere)
	UHitboxResponder* Responder;

	virtual void Enter(ABaseFighter& fighter) override;
	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
	virtual void Update(ABaseFighter& fighter) override;
	virtual void Exit(ABaseFighter& fighter) override;

	UFUNCTION(BlueprintNativeEvent)
	void AttackStateEnter(ABaseFighter* fighter);
	UFUNCTION(BlueprintNativeEvent)
	UFightState* AttackStateHandleInput(ABaseFighter* fighter);
	UFUNCTION(BlueprintNativeEvent)
	void AttackStateUpdate(ABaseFighter* fighter);
	UFUNCTION(BlueprintNativeEvent)
	void AttackStateExit(ABaseFighter* fighter);

protected:

	int CurrentFrame;
};

//TODO: ADJUST THIS TO TRANSITION TO ANY DESIRED STATE (THAT MAKES USE OF THE DATA TABLES?)
USTRUCT(Blueprintable, BlueprintType)
struct FStateToTransition
{
	GENERATED_BODY()

public:

	FStateToTransition();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFightState> State;
};

USTRUCT(Blueprintable, BlueprintType)
struct FStatesToTransitionButton : public FStateToTransition
{
	GENERATED_BODY()

public:

	FStatesToTransitionButton();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInputType Input;
};

//USTRUCT(Blueprintable, BlueprintType)
//struct FStatesToTransitionMotionInput : public FStateToTransition
//{
//	GENERATED_BODY()
//
//public:
//
//	TArray<EInputType> Inputs;
//};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UGroundedComboAttackState : public UGroundedAttackState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FStatesToTransitionButton State;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinCancelFrame;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxCancelFrame;

	virtual UFightState* HandleInput(ABaseFighter& fighter) override;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API USpecialMoveState : public UFightState
{
	GENERATED_BODY()
public:

	USpecialMoveState();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EInputType> RequiredInput;

	UMotionInput* MotionInput;

	//UMotionInput* ReturnMotionInput();
};

//UCLASS(Blueprintable, BlueprintType)
//class MYPROJECT_API USpecialMoveState : public UPrimaryDataAsset, public USpecialMoveState
//{
//	GENERATED_BODY()
//
//public:
//};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API USpecialMoveTransitionState : public USpecialMoveState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FStatesToTransitionButton State;

};
