// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Animation/BlendSpace1D.h"

#include "InputMappingContext.h"

#include "BaseStates.h"

#include "InputBuffer.h"

#include "Collision/UHitbox.h"
#include "Collision/HitboxHandler.h"

#include "Animation/FixedFrameRateAnimationComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "BaseFighter.generated.h"

//TODO: ADJUST THIS TO TRANSITION TO ANY DESIRED STATE (THAT MAKES USE OF THE DATA TABLES)
USTRUCT(Blueprintable, BlueprintType)
struct FSpecialMoves
{
	GENERATED_BODY()

public:

	FSpecialMoves();

	void Init();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFightState> State;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EInputType> RequiredInput;

	UMotionInput MotionInput;
};

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API ABaseFighter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHealth;
	UPROPERTY(EditAnywhere)
	float ForwardWalkSpeed;
	UPROPERTY(EditAnywhere)
	float BackwardWalkSpeed;

	UPROPERTY(EditAnywhere)
	float JumpForce;
	UPROPERTY(EditAnywhere)
	float JumpMoveForce;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	EInputType ForwardInput;
	EInputType BackwardInput;

	UInputBuffer* BufferHandler;

	UFightState* State;

	HitboxHandler* HitboxesHandler;

	bool FacingRight = 0;

	int FreezeTime = 0;

public:
	// Sets default values for this pawn's properties
	ABaseFighter();

	UFUNCTION(BlueprintCallable)
	void InitializeController();

	void WalkForward();
	void WalkBackward();
	void RotateTowardsDirection();
	void ResetPlayer();

	void ChangeState(UFightState* state);

	void AirCollisionCheck();

	/*UFUNCTION(BlueprintCallable)
	void ChangeToStunState();*/
	UFUNCTION(BlueprintCallable)
	void ChangeToBlockState(float knockback, int duration);
	UFUNCTION(BlueprintCallable)
	void ChangeToStunState(float knockback, int duration);
	UFUNCTION(BlueprintCallable)
	void ChangeToKnockbackState(float launch, float knockback);
	UFUNCTION(BlueprintCallable)
	void ChangeToGrabState();
	UFUNCTION(BlueprintCallable)
	void ChangeToGrabbedState();

	void SetFacingRight(bool side);

	UFUNCTION(BlueprintCallable)
	void StartInput();
	UFUNCTION(BlueprintCallable)
	void StopInput();

	UFUNCTION(BlueprintCallable)
	void AddSuperBar(float value);
	UFUNCTION(BlueprintCallable)
	void SetFreezeTime(int duration);
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damage);

	UFUNCTION(BlueprintCallable)
	bool IsHoldingBlock();

	UFUNCTION(BlueprintCallable)
	bool InputCheck(EInputType input);

	UFUNCTION(BlueprintCallable)
	UFightState* ReturnSpecialMoveByMotion();

	UFUNCTION(BlueprintCallable)
	const bool HasHitEnemy();

	UFUNCTION(BlueprintCallable)
	void PlayDefaultHitEffect(FVector position, FRotator rotation);

	UFUNCTION(BlueprintCallable)
	UGroundedAttackState* ReturnAttackState();
	UFUNCTION(BlueprintCallable)
	UGrabState* ReturnGrabState();

	UFUNCTION(BlueprintCallable)
	UFightState* GetCurrentState();

	UInputBuffer* ReturnInputBuffer();

	HitboxHandler* ReturnHitboxHandler();

	EInputType ReturnForwardInput();
	EInputType ReturnBackwardInput();

	UFUNCTION(BlueprintCallable)
	float GetJumpForce() const;

	UFUNCTION(BlueprintCallable)
	float GetJumpMoveForce() const;

	UFUNCTION(BlueprintCallable)
	bool IsFacingRight() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	UFUNCTION(BlueprintCallable)
	bool IsGrounded() const;
	UFUNCTION(BlueprintCallable)
	bool IsInBlockState() const;

	UFUNCTION(BlueprintCallable)
	FString GetInputBufferData();

	UFUNCTION(BlueprintCallable)
	FString GetInputBufferName();

	UFUNCTION(BlueprintCallable)
	FString GetInputBufferDataByIndex(int index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	float MaxSuperBar = 100.f;
	float CurrentSuperBar;

	//UCharacterMovementComponent* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHitbox* Hitbox;
	UPROPERTY(EditAnywhere)
	UHitbox* Grabbox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* FighterMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Pushbox;

	/*UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;*/

	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* TPose;

	UPROPERTY(EditAnywhere, Category = "Default animations")
	UBlendSpace* FallBlend;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UBlendSpace* NeutralJump;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* Idle;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* DuckCrouch;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* ForwardWalk;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* BackwardWalk;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* ForwardDash;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* BackwardDash;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* Laying;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* StandingUp;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* Stunned;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* Block;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* GrabStartUp;
	UPROPERTY(EditAnywhere, Category = "Default animations")
	UAnimSequence* GrabAttack;

	UPROPERTY(EditAnywhere)
	UHitboxResponder* GrabResponder;

	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> LightPunch;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> MediumPunch;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> HeavyPunch;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> LightKick;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> MediumKick;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> HeavyKick;


	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> CrouchLightPunch;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> CrouchMediumPunch;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> CrouchHeavyPunch;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> CrouchLightKick;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> CrouchMediumKick;
	UPROPERTY(EditAnywhere, Category = "Normal attacks")
	TSubclassOf<UGroundedAttackState> CrouchHeavyKick;

	UPROPERTY(EditAnywhere, Category = "Special moves")
	TArray <FSpecialMoves> SpecialMoves;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGrabState> GrabState;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UForwardDash> DashState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* LightPunchInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* LightKickInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* Up;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit VFX")
	UNiagaraSystem* NiagaraComponentEffectToPlay;

	USpecialMoveState* ReturnSpecialMove();

	/*UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UMotionInput* MotionInput;

	UPROPERTY(EditAnywhere)
	TArray<UMotionInput*> MotionInputs;*/

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	const int GetCurrentAnimationFrame() const;

private:
	
	void ButtonPressed(const FInputActionValue& value, const int index);
};
