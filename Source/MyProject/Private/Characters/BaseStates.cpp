// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseStates.h"

#include "Characters/BaseFighter.h"

#include "Collision/UHitbox.h"

#include "Animation/AnimSingleNodeInstance.h"

void UGroundedState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering default state"));
	fighter.GetMesh()->SetAnimation(fighter.Idle);
}

UFightState* UGroundedState::HandleInput(ABaseFighter& fighter)
{
	/*if (NextState != nullptr)
		return NextState;*/

	if (!fighter.IsAlive())
		return NewObject<ULayingState>();

	if (!fighter.IsGrounded())
		return NewObject<UAirborneState>();

	if (fighter.ReturnSpecialMoveByMotion() != nullptr)
		return fighter.ReturnSpecialMoveByMotion();

	if(fighter.ReturnInputBuffer()->MotionInputs[0]->MotionComplete())
		return NewObject<UForwardDash>();

	if(fighter.InputCheck(EInputType::LightPunch))
		return DuplicateObject(fighter.LightPunch.GetDefaultObject(), nullptr);

	for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num() > 0)
		{
			for (int j = i + 1; j < fighter.ReturnInputBuffer()->InputBufferItems.Num(); j++)
			{
				if (i == j)
					continue;

				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
					fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
					return NewObject<UForwardJumpState>();
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
					fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
					return NewObject<UBackwardJumpState>();
			}

			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UNeutralJumpState>();

			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UForwardWalkState>();
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UBackwardWalkState>();


			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Down && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UCrouchState>();
			/*if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::DownRight && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UCrouchState>();
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::DownLeft && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UCrouchState>();*/

			/*if (fighter.BufferHandler->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.BufferHandler->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return new AirborneState(1500.f);
			if (fighter.BufferHandler->InputBufferItems[i]->InputDirection == EInputType::MediumPunch && fighter.BufferHandler->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return new KnockbackStunState();*/
			/*if (fighter.BufferHandler->InputBufferItems[i]->InputDirection == EInputType::LightPunch && fighter.BufferHandler->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return fighter.ComboAttackState;*/
			/*if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::LightPunch && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.LightPunch.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::MediumPunch && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.MediumPunch.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::HeavyPunch && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.HeavyPunch.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::LightKick && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.LightKick.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::MediumKick && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.MediumKick.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::HeavyKick && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.HeavyKick.GetDefaultObject(), nullptr);
				}
			}*/

			/*if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::MediumPunch && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UGrabStartupState>();*/

			/*if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::LightPunch && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
			{
				for (int j = 0; j < fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num(); j++)
				{
					if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[j].CanExecute())
					{
						fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[j].SetUsedTrue();

						return fighter.AttackState;
					}
				}
			}*/
		}
	}

	return nullptr;
}

void UGroundedState::Update(ABaseFighter& fighter)
{
	fighter.RotateTowardsDirection();

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	FVector loc = fighter.GetActorLocation();

	loc.X = 0;

	/*if (loc.Z != (0 + (fighter.FighterMesh->GetUnscaledBoxExtent().Z)))
	{
		loc.Z = 0 + (fighter.FighterMesh->GetUnscaledBoxExtent().Z);

		fighter.SetActorLocation(loc);
	}*/
}

void UGroundedState::Exit(ABaseFighter& fighter)
{
}

void UCrouchState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering crouch state"));
	fighter.GetMesh()->SetAnimation(fighter.DuckCrouch);
}

UFightState* UCrouchState::HandleInput(ABaseFighter& fighter)
{
	for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num() > 0)
		{
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Down && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime <= 0)
				return NewObject<UGroundedState>();

			/*if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::DownRight && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime <= 0)
				downReleased = 1;
			else
			{
				downReleased = 0;

				break;
			}
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::DownLeft && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime <= 0)
				downReleased = 1;
			else
			{
				downReleased = 0;

				break;
			}*/
		}
	}

	/*if(downReleased)
		return NewObject<UGroundedState>();*/

	/*if (!fighter.IsAlive())
		return NewObject<ULayingState>();

	if (!fighter.IsGrounded())
		return NewObject<UAirborneState>();

	if (fighter.ReturnSpecialMoveByMotion() != nullptr)
		return fighter.ReturnSpecialMoveByMotion();

	if (fighter.ReturnInputBuffer()->MotionInputs[0]->MotionComplete())
		return NewObject<UForwardDash>();*/

	if (fighter.InputCheck(EInputType::LightPunch))
		return DuplicateObject(fighter.CrouchLightPunch.GetDefaultObject(), nullptr);

	/*for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num() > 0)
		{
			for (int j = i + 1; j < fighter.ReturnInputBuffer()->InputBufferItems.Num(); j++)
			{
				if (i == j)
					continue;

				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
					fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
					return NewObject<UForwardJumpState>();
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
					fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
					return NewObject<UBackwardJumpState>();
			}

			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UNeutralJumpState>();

			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UForwardWalkState>();
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
				return NewObject<UBackwardWalkState>();
		}
	}*/

	return nullptr;
}

void UCrouchState::Update(ABaseFighter& fighter)
{
	fighter.RotateTowardsDirection();

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	FVector loc = fighter.GetActorLocation();

	loc.X = 0;
}

void UCrouchState::Exit(ABaseFighter& fighter)
{
}

ULayingState::ULayingState()
{
	LayingTimer = 30.f;
}

ULayingState::ULayingState(float time)
{
	LayingTimer = time;
}

void ULayingState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering laying state"));
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());
	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	fighter.GetMesh()->SetAnimation(fighter.Laying);
}

UFightState* ULayingState::HandleInput(ABaseFighter& fighter)
{
	if (LayingTimer <= 0 && fighter.IsAlive())
		return NewObject<UStandingUpState>();

	return nullptr;
}

void ULayingState::Update(ABaseFighter& fighter)
{
	LayingTimer -= 1.f;

	UGroundedState::Update(fighter);
}

void ULayingState::Exit(ABaseFighter& fighter)
{
	UGroundedState::Exit(fighter);
}

void UStandingUpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering standing up state"));
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());
	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	fighter.GetMesh()->SetAnimation(fighter.StandingUp);
}

UFightState* UStandingUpState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= fighter.StandingUp->GetPlayLength())
		return NewObject<UGroundedState>();

	return nullptr;
}

void UStandingUpState::Update(ABaseFighter& fighter)
{
	UGroundedState::Update(fighter);
}

void UStandingUpState::Exit(ABaseFighter& fighter)
{
	UGroundedState::Exit(fighter);
}

void UForwardWalkState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering forward walk state"));
	fighter.GetMesh()->SetAnimation(fighter.ForwardWalk);
}

UFightState* UForwardWalkState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.ReturnSpecialMoveByMotion() != nullptr)
		return fighter.ReturnSpecialMoveByMotion();

	if (fighter.ReturnInputBuffer()->MotionInputs[0]->MotionComplete())
		return NewObject<UForwardDash>();

	for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		for (int j = 0; j < fighter.ReturnInputBuffer()->InputBufferItems.Num(); j++)
		{
			if (i == j)
				continue;

			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
				fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
			{
				return NewObject<UForwardJumpState>();
			}

		}

		if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime <= 0 ||
			(fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Right && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
				fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Left && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0))
			return NewObject<UGroundedState>();
	}

	return nullptr;
}

void UForwardWalkState::Update(ABaseFighter& fighter)
{
	fighter.WalkForward();
}

void UForwardWalkState::Exit(ABaseFighter& fighter)
{
	fighter.GetCharacterMovement()->Velocity = (FVector(0, 0, 0));
}

void UBackwardWalkState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering backward walk state"));
	fighter.GetMesh()->SetAnimation(fighter.BackwardWalk);
}

UFightState* UBackwardWalkState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.ReturnSpecialMoveByMotion() != nullptr)
		return fighter.ReturnSpecialMoveByMotion();

	for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
	{
		for (int j = 0; j < fighter.ReturnInputBuffer()->InputBufferItems.Num(); j++)
		{
			if (i == j)
				continue;

			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
				fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
			{
				return NewObject<UBackwardJumpState>();
			}

		}

		if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime <= 0 ||
			(fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Right && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
				fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Left && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0))
			return NewObject<UGroundedState>();
	}

	return nullptr;
}

void UBackwardWalkState::Update(ABaseFighter& fighter)
{
	fighter.WalkBackward();
}

void UBackwardWalkState::Exit(ABaseFighter& fighter)
{
	fighter.GetCharacterMovement()->Velocity = (FVector(0, 0, 0));
}

void UForwardDash::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering forward dash state"));

	DashImpulse = FVector(0, 400, 0);

	if (!fighter.IsFacingRight())
		DashImpulse = DashImpulse * -1;
	fighter.GetMesh()->SetPlayRate(1.f);
	fighter.GetMesh()->PlayAnimation(fighter.ForwardDash, 0);
	//fighter.GetCharacterMovement()->Velocity = (FVector(DashImpulse));

	CurrentFrame = 0;
}

UFightState* UForwardDash::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= fighter.ForwardDash->GetPlayLength())
		return NewObject<UGroundedState>();

	return nullptr;
}

void UForwardDash::Update(ABaseFighter& fighter)
{
	int frame = (int)(fighter.GetMesh()->GetPosition() * 60);

	/*FString frameText = FString::FromInt(frame);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Frame: ") + frameText);*/
}

void UForwardDash::Exit(ABaseFighter& fighter)
{
	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
}

UAirborneState::UAirborneState()
{
	ImpulseDirection = FVector(0, 0, 0);
	CurrentFallVelocity = 0.f;
}

UAirborneState::UAirborneState(FVector impulse)
{
	ImpulseDirection = impulse;
}

UAirborneState::UAirborneState(float velocity)
{
	CurrentFallVelocity = velocity;
}

void UAirborneState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering airborne state"));

	//fighter.FighterMesh->SetEnableGravity(1);
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, 0, CurrentFallVelocity));

	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity (FVector(0, 0, CurrentFallVelocity));
}

UFightState* UAirborneState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetActorLocation().Z <= 50.f && CurrentFallVelocity <= 0.f)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UAirborneState::Update(ABaseFighter& fighter)
{
	CurrentFallVelocity -= 25.f;

	if (CurrentFallVelocity > MaxFallVelocity)
		CurrentFallVelocity = MaxFallVelocity;
	if (CurrentFallVelocity < -MaxFallVelocity)
		CurrentFallVelocity = -MaxFallVelocity;

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, 0, CurrentFallVelocity));
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector(0, 0, CurrentFallVelocity));
	fighter.AirCollisionCheck();
}

void UAirborneState::Exit(ABaseFighter& fighter)
{
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	auto loc = fighter.GetActorLocation();

	loc.Z = 0;

	fighter.SetActorLocation(loc);
}

void UNeutralJumpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering neutral jump state"));

	//CurrentFallVelocity = 850.f;

	fighter.GetMesh()->SetAnimation(fighter.NeutralJump);
	CurrentFallVelocity = fighter.GetJumpForce();
	//fighter.FighterMesh->SetEnableGravity(1);
	UAirborneState::Enter(fighter);
}

UFightState* UNeutralJumpState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.IsGrounded() && fighter.FighterMesh->ComponentVelocity.Z <= 0)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UNeutralJumpState::Update(ABaseFighter& fighter)
{
	CurrentFallVelocity -= 25.f;

	if (CurrentFallVelocity > MaxFallVelocity)
		CurrentFallVelocity = MaxFallVelocity;
	if (CurrentFallVelocity < -MaxFallVelocity)
		CurrentFallVelocity = -MaxFallVelocity;

	if(CurrentFallVelocity == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Fall force is exactly zero!!!"));
	}

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, 0, CurrentFallVelocity));
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector(0, 0, CurrentFallVelocity));
	fighter.AirCollisionCheck();
}

void UNeutralJumpState::Exit(ABaseFighter& fighter)
{
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	auto loc = fighter.GetActorLocation();

	loc.Z = 0;

	fighter.SetActorLocation(loc);
}

UForwardJumpState::UForwardJumpState()
{
	ImpulseDirection = FVector(0, 0, 0);
	CurrentFallVelocity = 0.f;
}

UForwardJumpState::UForwardJumpState(FVector impulse)
{
	ImpulseDirection = impulse;
}

UForwardJumpState::UForwardJumpState(float velocity)
{
	CurrentFallVelocity = velocity;
}

void UForwardJumpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering forward jump state"));

	CurrentFallVelocity = fighter.GetJumpForce();

	ForwardVelocity = fighter.GetJumpMoveForce();

	if (!fighter.IsFacingRight())
		ForwardVelocity *= -1;

	//fighter.FighterMesh->SetEnableGravity(1);
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, ForwardVelocity, CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, ForwardVelocity, CurrentFallVelocity);
	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

UFightState* UForwardJumpState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.IsGrounded() && fighter.GetCharacterMovement()->Velocity.Z <= 0)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UForwardJumpState::Update(ABaseFighter& fighter)
{
	CurrentFallVelocity -= 25.f;

	if (CurrentFallVelocity > MaxFallVelocity)
		CurrentFallVelocity = MaxFallVelocity;
	if (CurrentFallVelocity < -MaxFallVelocity)
		CurrentFallVelocity = -MaxFallVelocity;

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, ForwardVelocity, CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, ForwardVelocity, CurrentFallVelocity);
	fighter.AirCollisionCheck();
}

void UForwardJumpState::Exit(ABaseFighter& fighter)
{
	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	auto loc = fighter.GetActorLocation();

	loc.Z = 0;

	fighter.SetActorLocation(loc);
}

UBackwardJumpState::UBackwardJumpState()
{
	ImpulseDirection = FVector(0, 0, 0);
	CurrentFallVelocity = 0.f;
}

UBackwardJumpState::UBackwardJumpState(FVector impulse)
{
	ImpulseDirection = impulse;
}

UBackwardJumpState::UBackwardJumpState(float velocity)
{
	CurrentFallVelocity = velocity;
}

void UBackwardJumpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering forward jump state"));

	CurrentFallVelocity = fighter.GetJumpForce();

	BackwardVelocity = -fighter.GetJumpMoveForce();

	if (!fighter.IsFacingRight())
		BackwardVelocity *= -1;

	//fighter.FighterMesh->SetEnableGravity(1);

	fighter.GetCharacterMovement()->Velocity = FVector(0, BackwardVelocity, CurrentFallVelocity);
	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

UFightState* UBackwardJumpState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.IsGrounded() && fighter.GetCharacterMovement()->Velocity.Z <= 0)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UBackwardJumpState::Update(ABaseFighter& fighter)
{
	CurrentFallVelocity -= 25.f;

	if (CurrentFallVelocity > MaxFallVelocity)
		CurrentFallVelocity = MaxFallVelocity;
	if (CurrentFallVelocity < -MaxFallVelocity)
		CurrentFallVelocity = -MaxFallVelocity;

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, BackwardVelocity, CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, BackwardVelocity, CurrentFallVelocity);
	fighter.AirCollisionCheck();
}

void UBackwardJumpState::Exit(ABaseFighter& fighter)
{
	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	auto loc = fighter.GetActorLocation();
	loc.Z = 0;

	fighter.SetActorLocation(loc);
}

UBlockStunState::UBlockStunState(int duration, float velocity)
{
	Pushback = velocity;
	StunDuration = duration;

	CurrentStunTime = 0;
}

void UBlockStunState::Init(int duration, float velocity)
{
	Pushback = velocity;
	StunDuration = duration;

	CurrentStunTime = 0;
}

void UBlockStunState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering Block state"));

	fighter.GetMesh()->SetAnimation(fighter.Block);

	//Pushback = 400.f;

	if (fighter.IsFacingRight())
		Pushback *= -1;

	fighter.GetCharacterMovement()->Velocity = FVector(0, Pushback, 0);
}

UFightState* UBlockStunState::HandleInput(ABaseFighter& fighter)
{
	if (CurrentStunTime >= StunDuration)
	{
		if (fighter.ReturnSpecialMoveByMotion() != nullptr)
			return fighter.ReturnSpecialMoveByMotion();

		if (fighter.ReturnInputBuffer()->MotionInputs[0]->MotionComplete())
			return NewObject<UForwardDash>();

		if (fighter.InputCheck(EInputType::LightPunch))
			return DuplicateObject(fighter.LightPunch.GetDefaultObject(), nullptr);

		for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
		{
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num() > 0)
			{
				for (int j = i + 1; j < fighter.ReturnInputBuffer()->InputBufferItems.Num(); j++)
				{
					if (i == j)
						continue;

					if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
						fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
						return NewObject<UForwardJumpState>();
					if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
						fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
						return NewObject<UBackwardJumpState>();
				}

				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UNeutralJumpState>();

				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UForwardWalkState>();
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UBackwardWalkState>();
			}
		}

		return NewObject<UGroundedState>();
	}

	return nullptr;
}

void UBlockStunState::Update(ABaseFighter& fighter)
{
	CurrentStunTime += 1;

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, Pushback, 0));

	fighter.GetCharacterMovement()->Velocity = FVector(0, Pushback, 0);
}

void UBlockStunState::Exit(ABaseFighter& fighter)
{
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
}

UKnockbackStunState::UKnockbackStunState()
{
	Pushback = 400.f;
	StunDuration = 30;

	CurrentStunTime = 0;
}

UKnockbackStunState::UKnockbackStunState(float pushback, int duration)
{
	Pushback = pushback;
	StunDuration = duration;

	CurrentStunTime = 0;
}

void UKnockbackStunState::Init(float pushback, int duration)
{
	Pushback = pushback;
	StunDuration = duration;

	CurrentStunTime = 0;
}

void UKnockbackStunState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering stun state"));

	fighter.GetMesh()->SetAnimation(fighter.Stunned);

	//Pushback = 400.f;

	if (fighter.IsFacingRight())
		Pushback *= -1;

	fighter.GetCharacterMovement()->Velocity = FVector(0, Pushback, 0);
}

UFightState* UKnockbackStunState::HandleInput(ABaseFighter& fighter)
{
	if (CurrentStunTime >= StunDuration)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UKnockbackStunState::Update(ABaseFighter& fighter)
{
	CurrentStunTime += 1;

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, Pushback, 0));

	fighter.GetCharacterMovement()->Velocity = FVector(0, Pushback, 0);
}

void UKnockbackStunState::Exit(ABaseFighter& fighter)
{
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
}

UAirStunState::UAirStunState()
{
}

UAirStunState::UAirStunState(float velocity, float horizontal)
{
	CurrentFallVelocity = velocity;
	HorizontalKnockback = horizontal;
}

void UAirStunState::Init(float velocity, float horizontal)
{
	CurrentFallVelocity = velocity;
	HorizontalKnockback = horizontal;
}

void UAirStunState::Enter(ABaseFighter& fighter)
{
	MaxFallVelocity = 1500.f;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering air stun state"));
	
	//HorizontalKnockback = 400.f;

	if (fighter.IsFacingRight())
		HorizontalKnockback *= -1;

	fighter.GetCharacterMovement()->Velocity = FVector(0, HorizontalKnockback, CurrentFallVelocity);
	fighter.GetMesh()->SetAnimation(fighter.FallBlend);
	FVector BlendParams(0, CurrentFallVelocity, 0);
	fighter.GetMesh()->GetSingleNodeInstance()->SetBlendSpacePosition(BlendParams);
	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

UFightState* UAirStunState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.IsGrounded() && fighter.GetCharacterMovement()->Velocity.Z <= 0)
		return NewObject<ULayingState>();

	return nullptr;
}

void UAirStunState::Update(ABaseFighter& fighter)
{
	CurrentStunTime += 1;

	CurrentFallVelocity -= 50.f;

	if (CurrentFallVelocity > MaxFallVelocity)
		CurrentFallVelocity = MaxFallVelocity;
	if (CurrentFallVelocity < -MaxFallVelocity)
		CurrentFallVelocity = -MaxFallVelocity;

	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector(0, HorizontalKnockback, CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, HorizontalKnockback, CurrentFallVelocity);

	FVector BlendParams(0, CurrentFallVelocity, 0);
	fighter.GetMesh()->GetSingleNodeInstance()->SetBlendSpacePosition(BlendParams);
	fighter.AirCollisionCheck();
}

void UAirStunState::Exit(ABaseFighter& fighter)
{
	//fighter.FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

UGrabStartupState::UGrabStartupState()
{
}

void UGrabStartupState::Enter(ABaseFighter& fighter)
{
	fighter.GetMesh()->SetAnimation(fighter.GrabStartUp);

	fighter.Grabbox->SetResponder(fighter.GrabResponder);

	CurrentFrame = 0;
}

UFightState* UGrabStartupState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.ReturnHitboxHandler()->ReturnCollidedActors().Num() > 0)
	{
		ABaseFighter* enemy = Cast<ABaseFighter>(fighter.ReturnHitboxHandler()->ReturnCollidedActors()[0]);

		//enemy->ChangeState()

		/*fighter.GrabState->SetEnemy(enemy);

		return fighter.GrabState;*/
	}

	if (fighter.GetMesh()->GetPosition() >= fighter.GrabStartUp->GetPlayLength())
		return NewObject<UGroundedState>();

	return nullptr;
}

void UGrabStartupState::Update(ABaseFighter& fighter)
{
	CurrentFrame = (int)(fighter.GetMesh()->GetPosition() * 60);

	FString frameText = FString::FromInt(CurrentFrame);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Frame: ") + frameText);

	if (CurrentFrame == MinFrame)
		fighter.Grabbox->OpenColliderState();

	if (CurrentFrame == MaxFrame)
		fighter.Grabbox->CloseColliderState();
}

void UGrabStartupState::Exit(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Exiting grab"));
	fighter.Grabbox->CloseColliderState();
	fighter.Grabbox->ClearCollidedObjects();
	fighter.ReturnHitboxHandler()->ClearCollidedObjects();
}

void UGrabState::Enter(ABaseFighter& fighter)
{
	fighter.GetMesh()->SetAnimation(fighter.GrabAttack);
}

UFightState* UGrabState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= fighter.GrabAttack->GetPlayLength())
		return NewObject<UGroundedState>();

	return nullptr;
}

void UGrabState::Update(ABaseFighter& fighter)
{
	//fighter.FighterMesh->ComponentVelocity = FVector(0, 0, 0);

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	int frame = (int)(fighter.GetMesh()->GetPosition() * 60);

	if (frame == DamageFrame)
	{
		EnemyFighter->TakeDamage(Damage);

		EnemyFighter->ChangeState(NewObject<UAirStunState>());
	}
}

void UGrabState::Exit(ABaseFighter& fighter)
{
	EnemyFighter = nullptr;
}

void UGrabState::SetEnemy(ABaseFighter* fighter)
{
	EnemyFighter = fighter;
}

void UGroundedAttackState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering attack state"));

	fighter.GetMesh()->PlayAnimation(AnimationSequenceToPlay, 0);

	fighter.Hitbox->SetResponder(Responder);

	CurrentFrame = 0;

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	AttackStateEnter(&fighter);

	//fighter.GetMesh()->SetPosition(.15f);
}

UFightState* UGroundedAttackState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= AnimationSequenceToPlay->GetPlayLength())
	{
		if (fighter.ReturnSpecialMoveByMotion() != nullptr)
			return fighter.ReturnSpecialMoveByMotion();

		if (fighter.ReturnInputBuffer()->MotionInputs[0]->MotionComplete())
			return NewObject<UForwardDash>();

		if (fighter.InputCheck(EInputType::LightPunch))
			return DuplicateObject(fighter.LightPunch.GetDefaultObject(), nullptr);

		for (int i = 0; i < fighter.ReturnInputBuffer()->InputBufferItems.Num(); i++)
		{
			if (fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer.Num() > 0)
			{
				for (int j = i + 1; j < fighter.ReturnInputBuffer()->InputBufferItems.Num(); j++)
				{
					if (i == j)
						continue;

					if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
						fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
						return NewObject<UForwardJumpState>();
					if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0 &&
						fighter.ReturnInputBuffer()->InputBufferItems[j]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[j]->Buffer[0].HoldTime > 0)
						return NewObject<UBackwardJumpState>();
				}

				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Top && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UNeutralJumpState>();

				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnForwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UForwardWalkState>();
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == fighter.ReturnBackwardInput() && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UBackwardWalkState>();


				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::Down && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UCrouchState>();
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::DownRight && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UCrouchState>();
				if (fighter.ReturnInputBuffer()->InputBufferItems[i]->InputDirection == EInputType::DownLeft && fighter.ReturnInputBuffer()->InputBufferItems[i]->Buffer[0].HoldTime > 0)
					return NewObject<UCrouchState>();
			}
		}

		return NewObject<UGroundedState>();
	}

	return AttackStateHandleInput(&fighter);
}

void UGroundedAttackState::Update(ABaseFighter& fighter)
{
	//fighter.FighterMesh->ComponentVelocity = FVector(0, 0, 0);

	//int frame = (int)(fighter.GetMesh()->GetPosition() * 60);

	//CurrentFrame += 1;

	//float p = float((float(CurrentFrame) / 60.f));

	//fighter.GetMesh()->SetPosition(p);

	CurrentFrame = (int)(fighter.GetMesh()->GetPosition() * 60);

	FString frameText = FString::FromInt(CurrentFrame);
	//FString TimeText = FString::SanitizeFloat (p);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Time: ") + TimeText);

	if (CurrentFrame == MinFrame)
	{
		fighter.Hitbox->SetRelativeLocation(BoxPosition - FVector(0, 0, fighter.GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() / 2.f));
		fighter.Hitbox->SetBoxExtent(BoxExtent);
		fighter.Hitbox->OpenColliderState();
	}

	if (CurrentFrame == MaxFrame)
	{
		fighter.Hitbox->SetRelativeLocation(FVector(0, 0, 0));
		fighter.Hitbox->SetBoxExtent(FVector(0, 0, 0));
		fighter.Hitbox->CloseColliderState();
	}

	AttackStateUpdate(&fighter);
}

void UGroundedAttackState::Exit(ABaseFighter& fighter)
{
	fighter.Hitbox->CloseColliderState();
	fighter.Hitbox->ClearCollidedObjects();
	fighter.ReturnHitboxHandler()->ClearCollidedObjects();

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	//fighter.GetMesh()->SetPlayRate(1);

	AttackStateExit(&fighter);
}

void UGroundedAttackState::AttackStateEnter_Implementation(ABaseFighter* fighter)
{

}

UFightState* UGroundedAttackState::AttackStateHandleInput_Implementation(ABaseFighter* fighter)
{
	return nullptr;
}

void UGroundedAttackState::AttackStateUpdate_Implementation(ABaseFighter* fighter)
{

}

void UGroundedAttackState::AttackStateExit_Implementation(ABaseFighter* fighter)
{

}

UFightState* UGroundedComboAttackState::HandleInput(ABaseFighter& fighter)
{
	if (CurrentFrame >= MinCancelFrame && CurrentFrame <= MaxCancelFrame)
	{
		if (fighter.HasHitEnemy())
		{
			if (fighter.InputCheck(State.Input))
				return DuplicateObject(State.State.GetDefaultObject(), nullptr);
		}
	}
	
	return UGroundedAttackState::HandleInput(fighter);
}

FStateToTransition::FStateToTransition() : State(nullptr)
{

}

FStatesToTransitionButton::FStatesToTransitionButton() : FStateToTransition(), Input(EInputType::LightPunch)
{

}

USpecialMoveState::USpecialMoveState()
{
	//MotionInput = new UMotionInput(RequiredInput);
}

//UMotionInput* USpecialMoveState::ReturnMotionInput()
//{
//	return MotionInput;
//}
