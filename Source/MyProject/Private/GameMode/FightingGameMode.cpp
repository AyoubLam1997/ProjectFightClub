// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FightingGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "AI/AIFighterControllerPawn.h"
#include "AI/BaseAIController.h"
#include <EnhancedInputSubsystems.h>

void AFightingGameMode::BeginPlay()
{
	//UWorld::GetFirstLocalPlayerFromController();

	FVector pos1 = FVector(0, -175, 0);
	FVector pos2 = FVector(0, 175, 0);
	FRotator rot1 = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters(); 
	SpawnInfo.bNoFail = true;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	P1Fighter = GetWorld()->SpawnActor<ABaseFighter>(FighterToSpawn, pos1, rot1, SpawnInfo);
	// DEV NOTE: This isn't the way to set the camera to the player. Update in the future
	GetWorld()->GetPlayerControllerIterator()->Get(0)->Possess(P1Fighter);
	P1Fighter->InitializeController();
	P1Fighter->StopInput();

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController, &cons);

	P2Fighter = GetWorld()->SpawnActor<ABaseFighter>(FighterToSpawn, pos2, rot1, SpawnInfo);
	//GetWorld()->GetPlayerControllerIterator()->Get(1)->Possess(P2Fighter);
	APlayerController* controller = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
	GetWorld()->AddController(controller);
	controller->Possess(P2Fighter);
	P2Fighter->InitializeController();
	P2Fighter->StopInput();

	AAIFighterControllerPawn* aiPawn = GetWorld()->SpawnActor<AAIFighterControllerPawn>(AIToSpawn, pos2, rot1, SpawnInfo);

	aiPawn->SpawnDefaultController();

	if(ABaseAIController* aiCont = Cast<ABaseAIController>(aiPawn->Controller))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Controller is AI"));

		aiCont->InitializeController(P2Fighter);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Controller is not AI"));

	float y = (P1Fighter->GetActorLocation().Y + P2Fighter->GetActorLocation().Y) / 2.f;

	FVector cameraPos = FVector(-500, y, 90);

	FTransform transform(FRotator{ 0.f, 0.f, 0.f }, cameraPos, FVector{ 1.f, 1.f, 1.f });
	UWorld* poWorld = GetWorld();
	Camera = poWorld->SpawnActor<ACameraActor>();
	Camera->SetActorTransform(transform);

	UCameraComponent* cam = Camera->FindComponentByClass<UCameraComponent>();

	/*cam->ProjectionMode = ECameraProjectionMode::Orthographic;
	cam->OrthoWidth = 2000.f;*/

	// PERSONAL NOTE: I HATE HOW UNREAL HANDLES CAMERAS. THIS DUMB & STUPID & DUMB
	APlayerController* playerController = Cast<APlayerController>(P1Fighter->Controller);

	playerController->SetViewTarget(Camera);

	CurrentTimer = 1.5f;

	GameState = EFighGameState::Countdown;

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	Super::BeginPlay();
}

void AFightingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch(GameState)
	{
	case EFighGameState::Countdown:
	{
		CurrentTimer -= DeltaTime;

		if (CurrentTimer <= 0)
			SwitchGameState(EFighGameState::Fighting);
	}
		break;
	case EFighGameState::Fighting:

		if (!P1Fighter->IsAlive() || !P2Fighter->IsAlive())
		{
			CurrentTimer = 1.5f;

			SwitchGameState(EFighGameState::RoundWin);
		}

		break;
	case EFighGameState::RoundWin:

		CurrentTimer -= DeltaTime;

		if (CurrentTimer <= 0)
		{
			CurrentTimer = 1.5f;

			P1Fighter->ResetPlayer();
			P2Fighter->ResetPlayer();

			SetPlayerRoundStart();

			SwitchGameState(EFighGameState::Countdown);
		}

		break;
	}

	if(P1Fighter->GetActorLocation().Y < P2Fighter->GetActorLocation().Y && !P1Fighter->IsFacingRight())
	{
		P1Fighter->SetFacingRight(1);
		P2Fighter->SetFacingRight(0);
	}
	else if (P1Fighter->GetActorLocation().Y > P2Fighter->GetActorLocation().Y && P1Fighter->IsFacingRight())
	{
		P1Fighter->SetFacingRight(0);
		P2Fighter->SetFacingRight(1);
	}

	FVector loc1 = P1Fighter->GetActorLocation();
	FVector loc2 = P2Fighter->GetActorLocation();

	Distance = fabsf(loc1.Y - loc2.Y);

	if(Distance > 2400.f)
	{
		if (loc1.Y >= loc2.Y)
		{
			loc1.Y = Camera->GetActorLocation().Y + 1200.f;
			loc2.Y = Camera->GetActorLocation().Y - 1200.f;
		}
		else if (loc1.Y <= loc2.Y)
		{
			loc1.Y = Camera->GetActorLocation().Y - 1200.f;
			loc2.Y = Camera->GetActorLocation().Y + 1200.f;
		}
	}

	if (loc1.Y > 1000.f)
		loc1.Y = 1000.f;
	if (loc1.Y < -1000.f)
		loc1.Y = -1000.f;
	if (loc2.Y > 1000.f)
		loc2.Y = 1000.f;
	if (loc2.Y < -1000.f)
		loc2.Y = -1000.f;

	P1Fighter->SetActorLocation(loc1);
	P2Fighter->SetActorLocation(loc2);

	float totalLocY = (loc1.Y + loc2.Y) / 2.f;

	if (totalLocY > -MaxLevelSize && totalLocY < MaxLevelSize)
	{
		float y = (P1Fighter->GetActorLocation().Y + P2Fighter->GetActorLocation().Y) / 2.f;

		FVector cameraPos = FVector(-400, y, 90);

		if(P1Fighter->GetActorLocation().Z > 90.f || P2Fighter->GetActorLocation().Z > 90.f)
		{
			float z = (P1Fighter->GetActorLocation().Z + P2Fighter->GetActorLocation().Z) / 2.f;
			cameraPos.Z = z;
		}

		FVector TweenPos = FMath::VInterpTo(Camera->GetActorLocation(), cameraPos, DeltaTime, 2.f);

		//Camera->SetActorLocation(TweenPos);
	}
	else
	{
		if (totalLocY < -MaxLevelSize)
		{
			FVector cameraPos = FVector(-400, -MaxLevelSize, 90);

			if (P1Fighter->GetActorLocation().Z > 90.f || P2Fighter->GetActorLocation().Z > 90.f)
			{
				float z = (P1Fighter->GetActorLocation().Z + P2Fighter->GetActorLocation().Z) / 2.f;
				cameraPos.Z = z;
			}

			FVector TweenPos = FMath::VInterpTo(Camera->GetActorLocation(), cameraPos, DeltaTime, 2.f);

			//Camera->SetActorLocation(TweenPos);
		}
		else if (totalLocY > MaxLevelSize)
		{
			FVector cameraPos = FVector(-400, MaxLevelSize, 90);

			if (P1Fighter->GetActorLocation().Z > 90.f || P2Fighter->GetActorLocation().Z > 90.f)
			{
				float z = (P1Fighter->GetActorLocation().Z + P2Fighter->GetActorLocation().Z) / 2.f;
				cameraPos.Z = z;
			}

			FVector TweenPos = FMath::VInterpTo(Camera->GetActorLocation(), cameraPos, DeltaTime, 2.f);

			//Camera->SetActorLocation(TweenPos);
		}
	}

	/*FRotator p1Rot = UKismetMathLibrary::FindLookAtRotation(P1Fighter->GetMesh()->GetComponentLocation(), Camera->GetActorLocation());
	FRotator p2Rot = UKismetMathLibrary::FindLookAtRotation(P2Fighter->GetMesh()->GetComponentLocation(), Camera->GetActorLocation());

	P1Fighter->GetMesh()->SetWorldRotation(FRotator(0, p1Rot.Pitch, 0));
	P2Fighter->GetMesh()->SetWorldRotation(p2Rot);*/
	
	//AirToGroundCollisionCheck();
}

void AFightingGameMode::SetPlayerRoundStart()
{
	FVector pos1 = FVector(0, -200, 0);
	FVector pos2 = FVector(0, 200, 0);

	P1Fighter->SetActorLocation(pos1);
	P2Fighter->SetActorLocation(pos2);
}

void AFightingGameMode::AirToGroundCollisionCheck()
{
	ABaseFighter* top = nullptr;
	ABaseFighter* bottom = nullptr;

	if ((P1Fighter->GetActorLocation().Z + P1Fighter->FighterMesh->GetUnscaledBoxExtent().Z) > (P2Fighter->GetActorLocation().Z + P2Fighter->FighterMesh->GetUnscaledBoxExtent().Z))
	{
		top = P1Fighter;
		bottom = P2Fighter;
	}
	else if ((P2Fighter->GetActorLocation().Z + P2Fighter->FighterMesh->GetUnscaledBoxExtent().Z) > (P1Fighter->GetActorLocation().Z + P1Fighter->FighterMesh->GetUnscaledBoxExtent().Z))
	{
		top = P2Fighter;
		bottom = P1Fighter;
	}

	if (top == nullptr)
		return;

	TArray<AActor*> actors;

	top->FighterMesh->GetOverlappingActors(actors);

	if(actors.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Top detecting collision"));

		if(actors.Contains(bottom))
		{
			/*FString s = FString::SanitizeFloat(top->GetActorLocation().Z + top->FighterMesh->GetUnscaledBoxExtent().Z);
			FString s2 = FString::SanitizeFloat(bottom->GetActorLocation().Z + bottom->FighterMesh->GetUnscaledBoxExtent().Z);

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *s);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *s2);*/

			// TODO: Adjust distance based on the size of the pushbox & the distance between the fighters
			if(top->GetActorLocation().Z == bottom->GetActorLocation().Z)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Heights are equal"));
			}
			if ((top->GetActorLocation().Y < bottom->GetActorLocation().Y) && (top->GetActorLocation().Z != bottom->GetActorLocation().Z))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Higher"));

				auto leftLoc = top->GetActorLocation();
				float leftY = leftLoc.Y - top->FighterMesh->GetUnscaledBoxExtent().Y;

				auto rightLox = bottom->GetActorLocation();
				float rightY = rightLox.Y + bottom->FighterMesh->GetUnscaledBoxExtent().Y;

				leftLoc.Y = leftY;
				rightLox.Y = rightY;

				top->SetActorLocation(leftLoc);
				bottom->SetActorLocation(rightLox);
			}
			else if (top->GetActorLocation().Y > bottom->GetActorLocation().Y && top->GetActorLocation().Z != bottom->GetActorLocation().Z)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Lower"));

				auto leftLoc = top->GetActorLocation();
				float leftY = leftLoc.Y + top->FighterMesh->GetUnscaledBoxExtent().Y;

				auto rightLox = bottom->GetActorLocation();
				float rightY = rightLox.Y - bottom->FighterMesh->GetUnscaledBoxExtent().Y;

				leftLoc.Y = leftY;
				rightLox.Y = rightY;

				top->SetActorLocation(leftLoc);
				bottom->SetActorLocation(rightLox);
			}
		}

		actors.Empty();
	}
}

void AFightingGameMode::SwitchGameState(EFighGameState state)
{
	if(state == EFighGameState::Fighting)
	{
		P1Fighter->StartInput();
		P2Fighter->StartInput();
	}
	else
	{
		P1Fighter->StopInput();
		P2Fighter->StopInput();
	}

	GameState = state;
}


void APlayArea::BeginPlay()
{
	FVector pos1 = FVector(0, -200, 0);
	FVector pos2 = FVector(0, 200, 0);
	FRotator rot1 = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();

	P1Fighter = GetWorld()->SpawnActor<ABaseFighter>(FighterToSpawn, pos1, rot1, SpawnInfo);
	// DEV NOTE: This isn't the way to set the camera to the player. Update in the future
	GetWorld()->GetPlayerControllerIterator()->Get(0)->Possess(P1Fighter);
	P1Fighter->InitializeController();

	P1Fighter->StartInput();
}

void APlayArea::Tick(float DeltaTime)
{

}
