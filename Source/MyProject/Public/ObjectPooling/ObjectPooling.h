// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPooling.generated.h"

class APoolObject;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UObjectPooling : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UObjectPooling();

protected:

	UPROPERTY()
	TArray<APoolObject*> ObjectPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APoolObject> PoolObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSize;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void InitializeObjectPool();

	UFUNCTION(BlueprintCallable)
	void SetPoolObject(TSubclassOf<APoolObject> Object);

	UFUNCTION(BlueprintCallable)
	void AddToPool(APoolObject* Object);

	UFUNCTION(BlueprintCallable)
	APoolObject* GetLatestPoolObject(FVector position, FRotator rotation);

	UFUNCTION(BlueprintCallable)
	TArray<APoolObject*> ReturnPool();

	UFUNCTION(BlueprintCallable)
	void SetMaxPoolSize(int Size);

	UFUNCTION(BlueprintCallable)
	int GetMaxPoolSize();

	UFUNCTION(BlueprintCallable)
	int GetCurrentPoolSize();
};
