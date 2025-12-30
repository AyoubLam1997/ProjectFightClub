// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseStates.h"

#include "Characters/BaseFighter.h"

#include "Collision/UHitbox.h"

#include "Animation/AnimSingleNodeInstance.h"

void UGroundedState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering default state"));
	fighter.GetMesh()->SetAnimation(fighter.m_Idle);
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
		return DuplicateObject(fighter.m_LightPunch.GetDefaultObject(), nullptr);

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

			/*if (fighter.m_BufferHandler->m_InputBufferItems[i]->InputDirection == EInputType::Top && fighter.m_BufferHandler->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
				return new AirborneState(1500.f);
			if (fighter.m_BufferHandler->m_InputBufferItems[i]->InputDirection == EInputType::MediumPunch && fighter.m_BufferHandler->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
				return new KnockbackStunState();*/
			/*if (fighter.m_BufferHandler->m_InputBufferItems[i]->InputDirection == EInputType::LightPunch && fighter.m_BufferHandler->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
				return fighter.m_ComboAttackState;*/
			/*if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::LightPunch && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.m_LightPunch.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::MediumPunch && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.m_MediumPunch.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::HeavyPunch && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.m_HeavyPunch.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::LightKick && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.m_LightKick.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::MediumKick && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.m_MediumKick.GetDefaultObject(), nullptr);
				}
			}
			if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::HeavyKick && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].CanExecute())
				{
					fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].SetUsedTrue();
					return DuplicateObject(fighter.m_HeavyKick.GetDefaultObject(), nullptr);
				}
			}*/

			/*if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::MediumPunch && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
				return NewObject<UGrabStartupState>();*/

			/*if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->InputDirection == EInputType::LightPunch && fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[0].m_HoldTime > 0)
			{
				for (int j = 0; j < fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer.Num(); j++)
				{
					if (fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[j].CanExecute())
					{
						fighter.ReturnInputBuffer()->m_InputBufferItems[i]->m_Buffer[j].SetUsedTrue();

						return fighter.m_AttackState;
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

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	FVector loc = fighter.GetActorLocation();

	loc.X = 0;

	/*if (loc.Z != (0 + (fighter.m_FighterMesh->GetUnscaledBoxExtent().Z)))
	{
		loc.Z = 0 + (fighter.m_FighterMesh->GetUnscaledBoxExtent().Z);

		fighter.SetActorLocation(loc);
	}*/
}

void UGroundedState::Exit(ABaseFighter& fighter)
{
}

void UCrouchState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering crouch state"));
	fighter.GetMesh()->SetAnimation(fighter.m_Crouch);
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

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	FVector loc = fighter.GetActorLocation();

	loc.X = 0;
}

void UCrouchState::Exit(ABaseFighter& fighter)
{
}

ULayingState::ULayingState()
{
	m_LayingTimer = 30.f;
}

ULayingState::ULayingState(float time)
{
	m_LayingTimer = time;
}

void ULayingState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering laying state"));
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());
	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	fighter.GetMesh()->SetAnimation(fighter.m_Laying);
}

UFightState* ULayingState::HandleInput(ABaseFighter& fighter)
{
	if (m_LayingTimer <= 0 && fighter.IsAlive())
		return NewObject<UStandingUpState>();

	return nullptr;
}

void ULayingState::Update(ABaseFighter& fighter)
{
	m_LayingTimer -= 1.f;

	UGroundedState::Update(fighter);
}

void ULayingState::Exit(ABaseFighter& fighter)
{
	UGroundedState::Exit(fighter);
}

void UStandingUpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering standing up state"));
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());
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
	fighter.GetMesh()->SetAnimation(fighter.m_ForwardWalk);
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
	fighter.GetMesh()->SetAnimation(fighter.m_BackwardWalk);
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

	m_DashImpulse = FVector(0, 400, 0);

	if (!fighter.IsFacingRight())
		m_DashImpulse = m_DashImpulse * -1;
	fighter.GetMesh()->SetPlayRate(1.f);
	fighter.GetMesh()->PlayAnimation(fighter.m_ForwardDash, 0);
	//fighter.GetCharacterMovement()->Velocity = (FVector(m_DashImpulse));

	m_CurrentFrame = 0;
}

UFightState* UForwardDash::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= fighter.m_ForwardDash->GetPlayLength())
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
	m_ImpulseDirection = FVector(0, 0, 0);
	m_CurrentFallVelocity = 0.f;
}

UAirborneState::UAirborneState(FVector impulse)
{
	m_ImpulseDirection = impulse;
}

UAirborneState::UAirborneState(float velocity)
{
	m_CurrentFallVelocity = velocity;
}

void UAirborneState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering airborne state"));

	//fighter.m_FighterMesh->SetEnableGravity(1);
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, 0, m_CurrentFallVelocity));

	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity (FVector(0, 0, m_CurrentFallVelocity));
}

UFightState* UAirborneState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetActorLocation().Z <= 50.f && m_CurrentFallVelocity <= 0.f)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UAirborneState::Update(ABaseFighter& fighter)
{
	m_CurrentFallVelocity -= 25.f;

	if (m_CurrentFallVelocity > m_MaxFallVelocity)
		m_CurrentFallVelocity = m_MaxFallVelocity;
	if (m_CurrentFallVelocity < -m_MaxFallVelocity)
		m_CurrentFallVelocity = -m_MaxFallVelocity;

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, 0, m_CurrentFallVelocity));
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector(0, 0, m_CurrentFallVelocity));
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

	//m_CurrentFallVelocity = 850.f;

	fighter.GetMesh()->SetAnimation(fighter.NeutralJump);
	m_CurrentFallVelocity = fighter.GetJumpForce();
	//fighter.m_FighterMesh->SetEnableGravity(1);
	UAirborneState::Enter(fighter);
}

UFightState* UNeutralJumpState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.IsGrounded() && fighter.m_FighterMesh->ComponentVelocity.Z <= 0)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UNeutralJumpState::Update(ABaseFighter& fighter)
{
	m_CurrentFallVelocity -= 25.f;

	if (m_CurrentFallVelocity > m_MaxFallVelocity)
		m_CurrentFallVelocity = m_MaxFallVelocity;
	if (m_CurrentFallVelocity < -m_MaxFallVelocity)
		m_CurrentFallVelocity = -m_MaxFallVelocity;

	if(m_CurrentFallVelocity == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Fall force is exactly zero!!!"));
	}

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, 0, m_CurrentFallVelocity));
	fighter.GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector(0, 0, m_CurrentFallVelocity));
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
	m_ImpulseDirection = FVector(0, 0, 0);
	m_CurrentFallVelocity = 0.f;
}

UForwardJumpState::UForwardJumpState(FVector impulse)
{
	m_ImpulseDirection = impulse;
}

UForwardJumpState::UForwardJumpState(float velocity)
{
	m_CurrentFallVelocity = velocity;
}

void UForwardJumpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering forward jump state"));

	m_CurrentFallVelocity = fighter.GetJumpForce();

	m_ForwardVelocity = fighter.GetJumpMoveForce();

	if (!fighter.IsFacingRight())
		m_ForwardVelocity *= -1;

	//fighter.m_FighterMesh->SetEnableGravity(1);
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, m_ForwardVelocity, m_CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_ForwardVelocity, m_CurrentFallVelocity);
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
	m_CurrentFallVelocity -= 25.f;

	if (m_CurrentFallVelocity > m_MaxFallVelocity)
		m_CurrentFallVelocity = m_MaxFallVelocity;
	if (m_CurrentFallVelocity < -m_MaxFallVelocity)
		m_CurrentFallVelocity = -m_MaxFallVelocity;

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, m_ForwardVelocity, m_CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_ForwardVelocity, m_CurrentFallVelocity);
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
	m_ImpulseDirection = FVector(0, 0, 0);
	m_CurrentFallVelocity = 0.f;
}

UBackwardJumpState::UBackwardJumpState(FVector impulse)
{
	m_ImpulseDirection = impulse;
}

UBackwardJumpState::UBackwardJumpState(float velocity)
{
	m_CurrentFallVelocity = velocity;
}

void UBackwardJumpState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering forward jump state"));

	m_CurrentFallVelocity = fighter.GetJumpForce();

	m_BackwardVelocity = -fighter.GetJumpMoveForce();

	if (!fighter.IsFacingRight())
		m_BackwardVelocity *= -1;

	//fighter.m_FighterMesh->SetEnableGravity(1);

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_BackwardVelocity, m_CurrentFallVelocity);
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
	m_CurrentFallVelocity -= 25.f;

	if (m_CurrentFallVelocity > m_MaxFallVelocity)
		m_CurrentFallVelocity = m_MaxFallVelocity;
	if (m_CurrentFallVelocity < -m_MaxFallVelocity)
		m_CurrentFallVelocity = -m_MaxFallVelocity;

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, m_BackwardVelocity, m_CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_BackwardVelocity, m_CurrentFallVelocity);
	fighter.AirCollisionCheck();
}

void UBackwardJumpState::Exit(ABaseFighter& fighter)
{
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());
	//fighter.m_FighterMesh->SetEnableGravity(0);

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

	//m_Pushback = 400.f;

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
			return DuplicateObject(fighter.m_LightPunch.GetDefaultObject(), nullptr);

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

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, m_Pushback, 0));

	fighter.GetCharacterMovement()->Velocity = FVector(0, Pushback, 0);
}

void UBlockStunState::Exit(ABaseFighter& fighter)
{
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
}

UKnockbackStunState::UKnockbackStunState()
{
	m_Pushback = 400.f;
	m_StunDuration = 30;

	m_CurrentStunTime = 0;
}

UKnockbackStunState::UKnockbackStunState(float pushback, int duration)
{
	m_Pushback = pushback;
	m_StunDuration = duration;

	m_CurrentStunTime = 0;
}

void UKnockbackStunState::Init(float pushback, int duration)
{
	m_Pushback = pushback;
	m_StunDuration = duration;

	m_CurrentStunTime = 0;
}

void UKnockbackStunState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering stun state"));

	fighter.GetMesh()->SetAnimation(fighter.m_Stunned);

	//m_Pushback = 400.f;

	if (fighter.IsFacingRight())
		m_Pushback *= -1;

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_Pushback, 0);
}

UFightState* UKnockbackStunState::HandleInput(ABaseFighter& fighter)
{
	if (m_CurrentStunTime >= m_StunDuration)
		return NewObject<UGroundedState>();

	return nullptr;
}

void UKnockbackStunState::Update(ABaseFighter& fighter)
{
	m_CurrentStunTime += 1;

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, m_Pushback, 0));

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_Pushback, 0);
}

void UKnockbackStunState::Exit(ABaseFighter& fighter)
{
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
}

UAirStunState::UAirStunState()
{
}

UAirStunState::UAirStunState(float velocity, float horizontal)
{
	m_CurrentFallVelocity = velocity;
	m_HorizontalKnockback = horizontal;
}

void UAirStunState::Init(float velocity, float horizontal)
{
	m_CurrentFallVelocity = velocity;
	m_HorizontalKnockback = horizontal;
}

void UAirStunState::Enter(ABaseFighter& fighter)
{
	m_MaxFallVelocity = 1500.f;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering air stun state"));
	
	//m_HorizontalKnockback = 400.f;

	if (fighter.IsFacingRight())
		m_HorizontalKnockback *= -1;

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_HorizontalKnockback, m_CurrentFallVelocity);
	fighter.GetMesh()->SetAnimation(fighter.m_FallBlend);
	FVector BlendParams(0, m_CurrentFallVelocity, 0);
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
	m_CurrentStunTime += 1;

	m_CurrentFallVelocity -= 50.f;

	if (m_CurrentFallVelocity > m_MaxFallVelocity)
		m_CurrentFallVelocity = m_MaxFallVelocity;
	if (m_CurrentFallVelocity < -m_MaxFallVelocity)
		m_CurrentFallVelocity = -m_MaxFallVelocity;

	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector(0, m_HorizontalKnockback, m_CurrentFallVelocity));

	fighter.GetCharacterMovement()->Velocity = FVector(0, m_HorizontalKnockback, m_CurrentFallVelocity);

	FVector BlendParams(0, m_CurrentFallVelocity, 0);
	fighter.GetMesh()->GetSingleNodeInstance()->SetBlendSpacePosition(BlendParams);
	fighter.AirCollisionCheck();
}

void UAirStunState::Exit(ABaseFighter& fighter)
{
	//fighter.m_FighterMesh->SetPhysicsLinearVelocity(FVector::Zero());

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();
	fighter.GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

UGrabStartupState::UGrabStartupState()
{
}

void UGrabStartupState::Enter(ABaseFighter& fighter)
{
	fighter.GetMesh()->SetAnimation(fighter.m_GrabStartUp);

	fighter.m_Grabbox->SetResponder(fighter.m_GrabResponder);

	m_CurrentFrame = 0;
}

UFightState* UGrabStartupState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.ReturnHitboxHandler()->ReturnCollidedActors().Num() > 0)
	{
		ABaseFighter* enemy = Cast<ABaseFighter>(fighter.ReturnHitboxHandler()->ReturnCollidedActors()[0]);

		//enemy->ChangeState()

		/*fighter.m_GrabState->SetEnemy(enemy);

		return fighter.m_GrabState;*/
	}

	if (fighter.GetMesh()->GetPosition() >= fighter.m_GrabStartUp->GetPlayLength())
		return NewObject<UGroundedState>();

	return nullptr;
}

void UGrabStartupState::Update(ABaseFighter& fighter)
{
	m_CurrentFrame = (int)(fighter.GetMesh()->GetPosition() * 60);

	FString frameText = FString::FromInt(m_CurrentFrame);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Frame: ") + frameText);

	if (m_CurrentFrame == m_MinFrame)
		fighter.m_Grabbox->OpenColliderState();

	if (m_CurrentFrame == m_MaxFrame)
		fighter.m_Grabbox->CloseColliderState();
}

void UGrabStartupState::Exit(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Exiting grab"));
	fighter.m_Grabbox->CloseColliderState();
	fighter.m_Grabbox->ClearCollidedObjects();
	fighter.ReturnHitboxHandler()->ClearCollidedObjects();
}

void UGrabState::Enter(ABaseFighter& fighter)
{
	fighter.GetMesh()->SetAnimation(fighter.m_GrabAttack);
}

UFightState* UGrabState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= fighter.m_GrabAttack->GetPlayLength())
		return NewObject<UGroundedState>();

	return nullptr;
}

void UGrabState::Update(ABaseFighter& fighter)
{
	//fighter.m_FighterMesh->ComponentVelocity = FVector(0, 0, 0);

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	int frame = (int)(fighter.GetMesh()->GetPosition() * 60);

	if (frame == m_DamageFrame)
	{
		m_EnemyFighter->TakeDamage(m_Damage);

		m_EnemyFighter->ChangeState(NewObject<UAirStunState>());
	}
}

void UGrabState::Exit(ABaseFighter& fighter)
{
	m_EnemyFighter = nullptr;
}

void UGrabState::SetEnemy(ABaseFighter* fighter)
{
	m_EnemyFighter = fighter;
}

void UGroundedAttackState::Enter(ABaseFighter& fighter)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering attack state"));

	fighter.GetMesh()->SetAnimation(m_AnimationSequence);

	fighter.m_Hitbox->SetResponder(m_Responder);

	m_CurrentFrame = 0;

	fighter.GetCharacterMovement()->Velocity = FVector::Zero();

	AttackStateEnter(&fighter);

	//fighter.GetMesh()->SetPosition(.15f);
}

UFightState* UGroundedAttackState::HandleInput(ABaseFighter& fighter)
{
	if (fighter.GetMesh()->GetPosition() >= m_AnimationSequence->GetPlayLength())
	{
		if (fighter.ReturnSpecialMoveByMotion() != nullptr)
			return fighter.ReturnSpecialMoveByMotion();

		if (fighter.ReturnInputBuffer()->MotionInputs[0]->MotionComplete())
			return NewObject<UForwardDash>();

		if (fighter.InputCheck(EInputType::LightPunch))
			return DuplicateObject(fighter.m_LightPunch.GetDefaultObject(), nullptr);

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
	//fighter.m_FighterMesh->ComponentVelocity = FVector(0, 0, 0);

	//int frame = (int)(fighter.GetMesh()->GetPosition() * 60);

	//m_CurrentFrame += 1;

	//float p = float((float(m_CurrentFrame) / 60.f));

	//fighter.GetMesh()->SetPosition(p);

	m_CurrentFrame = (int)(fighter.GetMesh()->GetPosition() * 60);

	FString frameText = FString::FromInt(m_CurrentFrame);
	//FString TimeText = FString::SanitizeFloat (p);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Time: ") + TimeText);

	if (m_CurrentFrame == m_MinFrame)
	{
		fighter.m_Hitbox->SetRelativeLocation(m_BoxPosition - FVector(0, 0, fighter.GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() / 2.f));
		fighter.m_Hitbox->SetBoxExtent(m_BoxExtent);
		fighter.m_Hitbox->OpenColliderState();
	}

	if (m_CurrentFrame == m_MaxFrame)
	{
		fighter.m_Hitbox->SetRelativeLocation(FVector(0, 0, 0));
		fighter.m_Hitbox->SetBoxExtent(FVector(0, 0, 0));
		fighter.m_Hitbox->CloseColliderState();
	}

	AttackStateUpdate(&fighter);
}

void UGroundedAttackState::Exit(ABaseFighter& fighter)
{
	fighter.m_Hitbox->CloseColliderState();
	fighter.m_Hitbox->ClearCollidedObjects();
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
	if (m_CurrentFrame >= m_MinCancelFrame && m_CurrentFrame <= m_MaxCancelFrame)
	{
		if (fighter.HasHitEnemy())
		{
			if (fighter.InputCheck(m_State.m_Input))
				return DuplicateObject(m_State.m_State.GetDefaultObject(), nullptr);
		}
	}
	
	return UGroundedAttackState::HandleInput(fighter);
}

FStateToTransition::FStateToTransition() : m_State(nullptr)
{

}

FStatesToTransitionButton::FStatesToTransitionButton() : FStateToTransition(), m_Input(EInputType::LightPunch)
{

}

USpecialMoveState::USpecialMoveState()
{
	//m_MotionInput = new UMotionInput(m_RequiredInput);
}

//UMotionInput* USpecialMoveState::ReturnMotionInput()
//{
//	return m_MotionInput;
//}
