// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooling/ObjectPooling.h"
#include "ObjectPooling/PoolObject.h"

// Sets default values for this component's properties
UObjectPooling::UObjectPooling()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ObjectPool = {};

	MaxSize = 0;
}


// Called when the game starts
void UObjectPooling::BeginPlay()
{
	Super::BeginPlay();

	InitializeObjectPool();
}

void UObjectPooling::InitializeObjectPool()
{
	for (int i = 0; i < MaxSize; i++)
	{
		FVector Position = FVector(-10000, -10000, 0);
		FRotator Rotation = FRotator(0, 0, 0);
		FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
		SpawnInfo.bNoFail = true;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APoolObject* Object = GetWorld()->SpawnActor<APoolObject>(PoolObject, Position, Rotation, SpawnInfo);
		Object->InitAndAddToPool(this);

		ObjectPool.Add(Object);
	}
}

void UObjectPooling::SetPoolObject(TSubclassOf<APoolObject> Object)
{
	PoolObject = Object;
}

void UObjectPooling::SetMaxPoolSize(int Size)
{
	MaxSize = Size;
}

// Called every frame
void UObjectPooling::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPooling::AddToPool(APoolObject* object)
{
	if (ObjectPool.Num() < MaxSize)
	{
		ObjectPool.Add(object);
	}
	else
	{
		GetWorld()->DestroyActor(object);
	}
}


APoolObject* UObjectPooling::GetLatestPoolObject(FVector position, FRotator rotation)
{
	if (ObjectPool.IsEmpty())
	{
		return nullptr;
	}

	APoolObject* Object = ObjectPool.Last();
	ObjectPool.Pop();

	Object->InitFromPool(position, rotation);

	return Object;
}

TArray<APoolObject*> UObjectPooling::ReturnPool()
{
	return ObjectPool;
}

int UObjectPooling::GetMaxPoolSize()
{
	return MaxSize;
}

int UObjectPooling::GetCurrentPoolSize()
{
	return ObjectPool.Num();
}
