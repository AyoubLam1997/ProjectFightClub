// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIFighterControllerPawn.h"

// Sets default values
AAIFighterControllerPawn::AAIFighterControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIFighterControllerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIFighterControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIFighterControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

