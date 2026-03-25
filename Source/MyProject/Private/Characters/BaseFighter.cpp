// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseFighter.h"
#include "Animation/FixedFrameRateAnimationComponent.h"
#include "Engine/GameEngine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/KismetStringLibrary.h>

FSpecialMoves::FSpecialMoves()
{
	//MotionInput->MotionInputs = RequiredInput;
}

void FSpecialMoves::Init()
{
	MotionInput.MotionInputs = RequiredInput;
}

// Sets default values
ABaseFighter::ABaseFighter()
{
	//FScriptDelegate ScriptDelegate;
	//ScriptDelegate.BindUFunction(this, FName("JumpOverlap"));
	//FighterMesh->OnComponentHit.Add(ScriptDelegate);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	/*comp = CreateDefaultSubobject<USceneComponent>(TEXT("Comp"));
	RootComponent = comp;*/
	
	FighterMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("FighterMesh"));
	FighterMesh->SetupAttachment(GetCapsuleComponent());

	Pushbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Pushbox"));
	Pushbox->SetupAttachment(GetCapsuleComponent());

	Pushbox->SetupAttachment(RootComponent);

	//NiagaraComponentEffectToPlay = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Hit VFX"));

	//RootComponent = comp;
	//FighterMesh->SetupAttachment(comp);

	//SetRootComponent(FighterMesh);

	//SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
	//SkeletalMesh->SetupAttachment(FighterMesh);
	/*SkeletalMesh->AddLocalOffset(FVector(0, 0, 0 - (Hurtbox->GetUnscaledBoxExtent().Z / 2.f)));*/

	BufferHandler = new UInputBuffer();

	//BufferHandler = NewObject<UInputBuffer>();

	//BufferHandler->add(MotionInputs);

	ForwardInput = EInputType::Right;
	BackwardInput = EInputType::Left;
}

// Called when the game starts or when spawned
void ABaseFighter::BeginPlay()
{
	//BufferHandler->Initialize();

	Super::BeginPlay();

	//Grabbox->AssignHitboxHandler(HitboxHandler);

	CurrentHealth = MaxHealth;
	CurrentSuperBar = 0;

	State = NewObject <UGroundedState>();
	State->AddToRoot();
	State->Enter(*this);

	Hitbox = FindComponentByClass<UHitbox>();
	//Grabbox = Cast<UHitbox>(GetDefaultSubobjectByName(TEXT("GrabBox")));

	HitboxesHandler = new HitboxHandler();

	Hitbox->AssignHitboxHandler(HitboxesHandler);

	TArray<EInputType> input;

	input.Add(EInputType::Right);
	input.Add(EInputType::Right);

	UMotionInput* dashInput = new UMotionInput();

	dashInput->MotionInputs = input;

	BufferHandler->MotionInputs.Add(dashInput);

	for (int i = 0; i < SpecialMoves.Num(); i++)
	{
		SpecialMoves[i].Init();
		BufferHandler->MotionInputs.Add(&SpecialMoves[i].MotionInput);
	}

	Pushbox->RegisterComponentWithWorld(GetWorld());

	//FighterMesh->OnComponentHit.AddDynamic(this, &ABaseFighter::OnHit);
	//Movement = FindComponentByClass<UCharacterMovementComponent>();

	//Movement->UpdatedComponent = Hurtbox;
}

void ABaseFighter::InitializeController()
{
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
			SubSystem->AddMappingContext(MappingContext, 0);
		else
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No enhanced input"));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No controller to control"));
}

// Called every frame
void ABaseFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*GroundedState* ground = Cast<GroundedState>(State);

	bool exists = (ground != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, UKismetStringLibrary::Conv_BoolToString(exists));*/

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(CurrentHealth));

	BufferHandler->BufferUpdate();
	BufferHandler->UpdateMotion(FacingRight);

	//for (int i = 0; i < BufferHandler->InputBufferItems.Num(); i++)
	//{
	//	if (BufferHandler->InputBufferItems[i]->InputDirection == EInputType::LightPunch)
	//	{
	//		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, UKismetStringLibrary::Conv_BoolToString(BufferHandler->InputBufferItems[i]->Buffer[0].IsUsed));
	//	}
	//}

	/*if(FreezeTime > 0)
	{
		FreezeTime -= 1;

		GetMesh()->GlobalAnimRateScale = 0.f;
		GetCharacterMovement()->Velocity = FVector::Zero();

		return;
	}*/

	/*if(GetMesh()->GlobalAnimRateScale == 0.f)
		GetMesh()->GlobalAnimRateScale = 1.f;*/

	/*for (int i = 0; i < BufferHandler->InputBufferItems.Num(); i++)
	{
		UInputBufferItem* item = BufferHandler->InputBufferItems[i];

		if (item->InputDirection == EInputType::LightPunch && item->Buffer[0].HoldTime == 1)
		{
			ChangeToStunState(125, 50);
		}
	}*/

	if (IsValid(State))
	{
		State->Update(*this);

		UFightState* newState = State->HandleInput(*this);

		if (IsValid(newState))
		{
			State->Exit(*this);

			State->RemoveFromRoot();

			UFightState* stateToDestroy = State;
			State = nullptr;
			State = newState;

			State->AddToRoot();
			State->Enter(*this);
		}
	}

	SetActorRotation(FQuat(0, 0, 0, 0));

	FVector loc = GetActorLocation();

	/*if (loc.Y > 2000.f)
	{
		loc.Y = 2000.f;

		FighterMesh->GetBodyInstance()->bLockYTranslation = true;
	}
	if (loc.Y < -2000.f)
	{
		loc.Y = -2000.f;
	}*/

	SetActorLocation(loc);
}

// Called to bind functionality to input
void ABaseFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	for (int i = 0; i < MappingContext->GetMappings().Num(); i++)
	{
		UInputBufferItem* item = new UInputBufferItem();

		EInputType input = InputFromString(MappingContext->GetMappings()[i].Action.GetName());

		if(input != EInputType::None)
		{
			item->AssignDirection(input);

			BufferHandler->InputBufferItems.Add(item);

			EnhancedInput->BindAction(MappingContext->GetMappings()[i].Action, ETriggerEvent::Triggered, this, &ABaseFighter::ButtonPressed, BufferHandler->InputBufferItems.Num() - 1);
			EnhancedInput->BindAction(MappingContext->GetMappings()[i].Action, ETriggerEvent::Completed, this, &ABaseFighter::ButtonPressed, BufferHandler->InputBufferItems.Num() - 1);
		}
	}
}

void ABaseFighter::WalkForward()
{
	if (FighterMesh != nullptr)
	{
		float dir = 0;

		if (FacingRight)
			dir = ForwardWalkSpeed;
		else if (!FacingRight)
			dir = -ForwardWalkSpeed;

		//FighterMesh->SetPhysicsLinearVelocity(FVector(0, dir, 0));

		GetCharacterMovement()->Velocity = (FVector(0, dir, 0));
	}
}

void ABaseFighter::WalkBackward()
{
	if (FighterMesh != nullptr)
	{
		float dir = 0;

		if (FacingRight)
			dir = -BackwardWalkSpeed;
		else if (!FacingRight)
			dir = BackwardWalkSpeed;

		//FighterMesh->SetPhysicsLinearVelocity(FVector(0, dir, 0));

		GetCharacterMovement()->Velocity = (FVector(0, dir, 0));
	}
}

void ABaseFighter::RotateTowardsDirection()
{
	if (FacingRight)
	{
		GetCapsuleComponent()->SetWorldScale3D(FVector(1, 1, 1));
	}
	else if (!FacingRight)
	{
		GetCapsuleComponent()->SetWorldScale3D(FVector(1, -1, 1));
	}
}

void ABaseFighter::AirCollisionCheck()
{
	TArray<AActor*> actors;

	Pushbox->GetOverlappingActors(actors);

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("Checking collision"));

	if (actors.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Collision has been detected"));

		ABaseFighter* other = Cast<ABaseFighter>(actors[0]);

		if (other == nullptr)
			return;

		//double direction = GetActorLocation().Y - other->GetActorLocation().Y;

		double total = Pushbox->GetUnscaledBoxExtent().Y + other->Pushbox->GetUnscaledBoxExtent().Y;

		/*FVector v = FVector(0, total, 0);

		double length = v.Length();

		double lengthSquared = sqrt(length);

		v.Normalize();

		double depth = total - lengthSquared;

		double penetration = v.Y / depth;

		double distance = (depth / 2.0) * v.Y;*/

		if (FacingRight)
		{
			SetActorLocation(FVector(GetActorLocation().X, other->GetActorLocation().Y - (total), GetActorLocation().Z));
		}
		else if (!FacingRight)
		{
			SetActorLocation(FVector(GetActorLocation().X, other->GetActorLocation().Y + (total), GetActorLocation().Z));
		}

		/*double boxSize = Pushbox->GetUnscaledBoxExtent().Y;

		double z = boxSize;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::SanitizeFloat(z));

		if (FacingRight)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y - z, GetActorLocation().Z));
		}
		else if (!FacingRight)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + z, GetActorLocation().Z));
		}*/
	}
}

void ABaseFighter::ResetPlayer()
{
	CurrentHealth = MaxHealth;

	ChangeState(NewObject<UGroundedState>());
}

void ABaseFighter::ChangeState(UFightState* state)
{
	State->Exit(*this);

	State->RemoveFromRoot();

	UFightState* stateToDestroy = State;
	State = nullptr;
	State = state;

	State->AddToRoot();
	State->Enter(*this);
}

//void ABaseFighter::ChangeToStunState()
//{
//	//ChangeState(NewObject<UKnockbackStunState>());
//
//	UAirStunState* state = NewObject<UAirStunState>();
//	//state->Init(1500, 400);
//	//State->NextState = state;
//
//	ChangeState(NewObject<UKnockbackStunState>());
//}

void ABaseFighter::ChangeToBlockState(float knockback, int duration)
{
	//ChangeState(NewObject<UKnockbackStunState>());

	UBlockStunState* state = NewObject<UBlockStunState>();
	//state->Init(1500, 400);
	//State->NextState = state;
	state->Init(duration, knockback);
	ChangeState(state);
}

void ABaseFighter::ChangeToStunState(float knockback, int duration)
{
	//ChangeState(NewObject<UKnockbackStunState>());

	UKnockbackStunState* state = NewObject<UKnockbackStunState>();
	//state->Init(1500, 400);
	//State->NextState = state;
	state->Init(knockback, duration);
	ChangeState(state);
}

void ABaseFighter::ChangeToKnockbackState(float launch, float knockback)
{
	//ChangeState(NewObject<UKnockbackStunState>());

	UAirStunState* state = NewObject<UAirStunState>();
	//state->Init(1500, 400);
	//State->NextState = state;
	state->Init(launch, knockback);
	ChangeState(state);
}

void ABaseFighter::ChangeToGrabState()
{
	ChangeState(DuplicateObject(GrabState.GetDefaultObject(), nullptr));
}

void ABaseFighter::ChangeToGrabbedState()
{
	//ChangeState(new KnockbackStunState());
}

void ABaseFighter::ButtonPressed(const FInputActionValue& value, const int index)
{
	const bool pressed = value.Get<bool>();

	BufferHandler->InputBufferItems[index]->SetInputActionPressed(pressed);
}

void ABaseFighter::AddSuperBar(float value)
{
	CurrentSuperBar += value;

	if (CurrentSuperBar >= MaxSuperBar)
		CurrentSuperBar = MaxSuperBar;
}

void ABaseFighter::SetFreezeTime(int duration)
{
	FreezeTime = duration;
}

void ABaseFighter::TakeDamage(float damage)
{
	if (damage < 0)
		return;

	CurrentHealth -= damage;
}

bool ABaseFighter::IsHoldingBlock()
{
	UGroundedState* fightState = Cast<UGroundedState>(State);
	bool exists = (fightState != nullptr);

	if (!exists)
		return 0;

	bool IsHoldingBack = 0;

	for (int i = 0; i < ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		for (int j = 1; j < ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num(); j++)
		{
			if(ReturnInputBuffer()->InputBufferItems[i]->InputDirection == ReturnBackwardInput())
			{
				if(ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				{
					IsHoldingBack = 1;
				}

				break;
			}
		}
	}

	return IsHoldingBack;
}

bool ABaseFighter::InputCheck(EInputType input)
{
	for (int i = 0; i < ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		if (ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num() > 0)
		{
			if (ReturnInputBuffer()->InputBufferItems[i]->InputDirection == input)
			{
				//DEV NOTE: 0 is the unnused state for the buffer. Start with 1 for input buffer check. BUG!!! LOOK INTO THIS WHY IT HAPPENS IN UE5 & NOT IN UNITY!!!!
				for (int j = 0; j < ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num(); j++)
				{
					if (ReturnInputBuffer()->InputBufferItems[i]->Buffer[j].CanExecute())
					{
						ReturnInputBuffer()->InputBufferItems[i]->Buffer[j].SetUsedTrue();

						// For debugging purposes
						int value = BufferHandler->InputBufferItems[i]->Buffer[j].HoldTime;

						return 1;
					}
				}
			}
			else
				continue;
		}
	}

	return 0;
}

UFightState* ABaseFighter::ReturnSpecialMoveByMotion()
{
	for (int i = 0; i < SpecialMoves.Num(); i++)
	{
		if(SpecialMoves[i].MotionInput.MotionComplete())
			return DuplicateObject(SpecialMoves[i].State.GetDefaultObject(), nullptr);
	}

	return nullptr;
}

const bool ABaseFighter::HasHitEnemy()
{
	if (HitboxesHandler->ReturnCollidedActors().Num() > 0)
		return 1;

	return 0;
}

UFightState* ABaseFighter::GetCurrentState()
{
	return State;
}

UGroundedAttackState* ABaseFighter::ReturnAttackState()
{
	// DEV NOTE: Dynamic casting needs to be more tested. Since RTTI is enabled, UE is running a tad slower.
	// The bigger issue, however, is that dynamic cast may cause inaccuracies (incorrect state/data, no state at all).
	// This is now implemented due to UE being extremely difficult with checking & returning what state the player is currently in.
	// TODO: Ask other devs for feedback/help
	UGroundedAttackState* fightState = Cast<UGroundedAttackState>(State);
	bool exists = (fightState != nullptr);

	if (exists)
		return fightState;

	return nullptr;
}

UGrabState* ABaseFighter::ReturnGrabState()
{
	// DEV NOTE: Dynamic casting needs to be more tested. Since RTTI is enabled, UE is running a tad slower.
	// The bigger issue, however, is that dynamic cast may cause inaccuracies (incorrect state/data, no state at all).
	// This is now implemented due to UE being extremely difficult with checking & returning what state the player is currently in.
	// TODO: Ask other devs for feedback/help
	UGrabState* fightState = Cast<UGrabState>(State);
	bool exists = (fightState != nullptr);

	if (exists)
		return fightState;

	return nullptr;
}

bool ABaseFighter::IsAlive() const
{
	if (CurrentHealth > 0)
		return 1;

	return 0;
}

float ABaseFighter::GetJumpForce() const
{
	return JumpForce;
}

float ABaseFighter::GetJumpMoveForce() const
{
	return JumpMoveForce;
}

bool ABaseFighter::IsFacingRight() const
{
	return FacingRight;
}

UInputBuffer* ABaseFighter::ReturnInputBuffer()
{
	return BufferHandler;
}

HitboxHandler* ABaseFighter::ReturnHitboxHandler()
{
	return HitboxesHandler;
}

EInputType ABaseFighter::ReturnForwardInput()
{
	return ForwardInput;
}

EInputType ABaseFighter::ReturnBackwardInput()
{
	return BackwardInput;
}

void ABaseFighter::SetFacingRight(bool side)
{
	FacingRight = side;

	if (FacingRight)
	{
		ForwardInput = EInputType::Right;
		BackwardInput = EInputType::Left;
	}
	else if (!FacingRight)
	{
		ForwardInput = EInputType::Left;
		BackwardInput = EInputType::Right;
	}
}

bool ABaseFighter::IsGrounded() const
{
	if (FighterMesh != nullptr)
	{
		auto loc = GetActorLocation().Z;

		if (loc > 0)
			return 0;
		else if (loc <= 0)
			return 1;
	}

	return 0;
}

const int ABaseFighter::GetCurrentAnimationFrame() const
{
	return (int)(GetMesh()->GetPosition() * 60);
}

void ABaseFighter::StartInput()
{
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Enabling input"));
		EnableInput(playerController);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No input to enable"));
}

void ABaseFighter::StopInput()
{
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Disabling input"));
		DisableInput(playerController);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No input to disable"));
}

void ABaseFighter::PlayDefaultHitEffect(FVector position, FRotator rotation)
{
	//NiagaraComponentEffectToPlay->SetWorldLocationAndRotation(position, rotation);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraComponentEffectToPlay, position, rotation);
	//NiagaraComponentEffectToPlay->Activate();
}

// TODO: Fix stutter look when players collide during the check
void ABaseFighter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABaseFighter* top = nullptr;
	ABaseFighter* bottom = Cast<ABaseFighter>(OtherActor);

	FVector loc = GetActorLocation();

	if(!FacingRight && loc.Y >= 2000)
	{
		double dis = fabsf(bottom->GetActorLocation().Y - loc.Y);

		double col = ((FighterMesh->GetUnscaledBoxExtent().Y / 2) + (bottom->FighterMesh->GetUnscaledBoxExtent().Y / 2));

		double difference = dis - col;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Box: ") + FString::SanitizeFloat(FighterMesh->GetUnscaledBoxExtent().Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Distance: ") + FString::SanitizeFloat(dis));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Collision: ") + FString::SanitizeFloat(col));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Difference: ") + FString::SanitizeFloat(difference));

		if (dis < col)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("lmao 2"));
		{
			bottom->SetActorLocation(FVector(bottom->GetActorLocation().X, GetActorLocation().Y - (FighterMesh->GetUnscaledBoxExtent().Y * 2), bottom->GetActorLocation().Z));
			bottom->FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());
		}
	}

	//ABaseFighter* temp = Cast<ABaseFighter>(OtherActor);

	//if (temp != nullptr)
	//{
	//	if ((this->GetActorLocation().Z + this->FighterMesh->GetUnscaledBoxExtent().Z) > (OtherActor->GetActorLocation().Z + temp->FighterMesh->GetUnscaledBoxExtent().Z))
	//	{
	//		top = this;
	//		bottom = temp;
	//	}
	//	else if ((OtherActor->GetActorLocation().Z + temp->FighterMesh->GetUnscaledBoxExtent().Z) > (this->GetActorLocation().Z + this->FighterMesh->GetUnscaledBoxExtent().Z))
	//	{
	//		top = temp;
	//		bottom = this;
	//	}

	//	if (top == nullptr || top != this)
	//		return;

	//	/*FString s = FString::SanitizeFloat(top->GetActorLocation().Z + top->FighterMesh->GetUnscaledBoxExtent().Z);
	//	FString s2 = FString::SanitizeFloat(bottom->GetActorLocation().Z + bottom->FighterMesh->GetUnscaledBoxExtent().Z);

	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *s);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *s2);*/

	//	// TODO: Adjust distance based on the size of the pushbox & the distance between the fighters
	//	if ((top->GetActorLocation().Y < bottom->GetActorLocation().Y) && (top->GetActorLocation().Z != bottom->GetActorLocation().Z) && top->GetCurrentState() == dynamic_cast<UAirborneState*>(top->GetCurrentState()) && (top->FighterMesh->GetComponentVelocity().Z < 0))
	//	{
	//		float distance = bottom->GetActorLocation().Y - top->GetActorLocation().Y;

	//		float col = (top->FighterMesh->GetUnscaledBoxExtent().Y) + (bottom->FighterMesh->GetUnscaledBoxExtent().Y);

	//		float dif = col - distance;

	//		auto leftLoc = top->GetActorLocation();
	//		float leftY = leftLoc.Y - (dif / 2);

	//		auto rightLox = bottom->GetActorLocation();
	//		float rightY = rightLox.Y + (dif / 2);

	//		leftLoc.Y = leftY;
	//		rightLox.Y = rightY;

	//		top->SetActorLocation(leftLoc);
	//		bottom->SetActorLocation(rightLox);
	//	}
	//	else if (top->GetActorLocation().Y > bottom->GetActorLocation().Y && top->GetActorLocation().Z != bottom->GetActorLocation().Z && top->GetCurrentState() == dynamic_cast<UAirborneState*>(top->GetCurrentState()) && (top->FighterMesh->GetComponentVelocity().Z < 0))
	//	{
	//		float distance = top->GetActorLocation().Y - bottom->GetActorLocation().Y;

	//		float col = (top->FighterMesh->GetUnscaledBoxExtent().Y) + (bottom->FighterMesh->GetUnscaledBoxExtent().Y);

	//		float dif = col - distance;

	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(distance));
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(col));
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(dif));

	//		auto leftLoc = top->GetActorLocation();
	//		float leftY = leftLoc.Y + (dif / 2);

	//		auto rightLox = bottom->GetActorLocation();
	//		float rightY = rightLox.Y - (dif / 2);

	//		leftLoc.Y = leftY;
	//		rightLox.Y = rightY;

	//		top->SetActorLocation(leftLoc);
	//		bottom->SetActorLocation(rightLox);
	//	}
	//}
	//else
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No temp fighter"));
}

USpecialMoveState* ABaseFighter::ReturnSpecialMove()
{
	/*for(int i = 0; i < SpecialMoves.Num(); i++)
	{
		if (SpecialMoves[i].GetDefaultObject()->MotionInput->MotionComplete())
			return SpecialMoves[i];
	}*/

	return nullptr;
}

bool ABaseFighter::IsInBlockState() const
{
	UBlockState* fightState = Cast<UBlockState>(State);
	bool exists = (fightState != nullptr);

	return exists;
}

FString ABaseFighter::GetInputBufferData()
{
	FString strin = InputToString(ReturnInputBuffer()->InputBufferItems[0]->InputDirection) + ": ";

	for(int i = 0; i < ReturnInputBuffer()->InputBufferItems[0]->Buffer.Num(); i++)
	{
		strin.Append(FString::FromInt(ReturnInputBuffer()->InputBufferItems[0]->Buffer[i].HoldTime));

		if (i < ReturnInputBuffer()->InputBufferItems[0]->Buffer.Num() - 1)
			strin.Append(" ");
	}

	return strin;
}

FString ABaseFighter::GetInputBufferName()
{
	return InputToString(ReturnInputBuffer()->InputBufferItems[0]->InputDirection) + ": ";
}

FString ABaseFighter::GetInputBufferDataByIndex(int index)
{
	return FString::FromInt(ReturnInputBuffer()->InputBufferItems[0]->Buffer[index].HoldTime);
}
