// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooling/PoolObject.h"
#include "ObjectPooling/ObjectPooling.h"

// Sets default values
APoolObject::APoolObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OwningPool = nullptr;

	bInUse = false;
}

// Called when the game starts or when spawned
void APoolObject::InitAndAddToPool(UObjectPooling* owner)
{
	OwningPool = owner;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);

	bInUse = false;
}

// Called every frame
void APoolObject::ReturnToPool()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);

	bInUse = false;

	if (OwningPool != nullptr)
		OwningPool->AddToPool(this);
}

// Called when the game starts or when spawned
void APoolObject::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);

	bInUse = false;
}

// Called every frame
void APoolObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void APoolObject::InitFromPool(FVector position, FRotator rotation)
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);

	bInUse = true;

	SetActorLocationAndRotation(position, rotation);

	InitFromPoolEvent(position, rotation);
}

// Called when the game starts or when spawned
void APoolObject::InitFromPoolEvent_Implementation(FVector position, FRotator rotation)
{

}

bool APoolObject::IsInUse() const
{
	return bInUse;
}
