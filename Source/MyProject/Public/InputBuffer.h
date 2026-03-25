// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InputMappingContext.h"

#include "InputBuffer.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EInputType
{
	None = 0,
	Top,
	TopRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	TopLeft,
	LightPunch,
	MediumPunch,
	HeavyPunch,
	LightKick,
	MediumKick,
	HeavyKick
};

FString InputToString(EInputType type);

EInputType InputFromString(FString string);

class MYPROJECT_API UMotionInput
{
public:

	UMotionInput();
	UMotionInput(TArray<EInputType> motions);
	~UMotionInput() {};

	void BufferCheck();
	void IncreaseIndex();
	void ResetInput();

	bool MotionComplete();
	bool InputCheck(EInputType input);

	TArray<EInputType> MotionInputs;

	int BufferTime;
	int IndexCheck = 0;

	bool MotionUsed;
};

class MYPROJECT_API UInputStateItem
{
public:

	bool CanExecute();
	bool CanMotionExecute();

	void HoldUp();
	void ReleasedUp();
	void SetUsedTrue();
	void SetMotionTrue();
	void SetHoldUsed(int time, bool used, bool motion);

	int HoldTime = 0;

	bool IsUsed = 0;
	bool MotionUsed = 0;
};

class MYPROJECT_API UInputBufferItem
{
public:

	UInputBufferItem();
	UInputBufferItem(EInputType direction);
	~UInputBufferItem() {};

	void InputCheck();
	void SetInputActionPressed(bool pressed);
	void AssignDirection(EInputType direction);
	void SetHoldUsed(int index, int time, bool used, bool motion);

	EInputType InputDirection;

	UInputAction* Action;

	bool InputActionPressed = 0;

	TArray<UInputStateItem> Buffer;

protected:

};

class MYPROJECT_API UInputBuffer
{
public:

	static const int m_BufferWindow = 12;

	UInputBuffer();
	UInputBuffer(TArray<UMotionInput*>& inputs);
	~UInputBuffer();

	void Initialize();
	void BufferUpdate();

	void add(TArray<UMotionInput*>& inputs);

	void UpdateMotion(bool right);

	TArray<UInputBufferItem*> InputBufferItems;
	TArray<UMotionInput*> MotionInputs;
};
