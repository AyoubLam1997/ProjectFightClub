// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolObject.generated.h"

class UObjectPooling;

UCLASS()
class MYPROJECT_API APoolObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolObject();

protected:

	UPROPERTY()
	UObjectPooling* OwningPool;

	UPROPERTY()
	bool bInUse;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void InitAndAddToPool(UObjectPooling* owner);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void InitFromPool(FVector position, FRotator rotation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitFromPoolEvent(FVector position, FRotator rotation);
	UFUNCTION(BlueprintCallable)
	virtual void ReturnToPool();

	UFUNCTION(BlueprintCallable)
	bool IsInUse() const;
};
