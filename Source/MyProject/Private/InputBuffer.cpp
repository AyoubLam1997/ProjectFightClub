// Fill out your copyright notice in the Description page of Project Settings.

#include "InputBuffer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

using namespace std;

FString InputToString(EInputType type)
{
    switch (type)
    {
    case EInputType::None:
        return "None";
    case EInputType::Top:
        return "Top";
    case EInputType::TopRight:
        return "TopRight";
    case EInputType::Right:
        return "Right";
    case EInputType::DownRight:
        return "DownRight";
    case EInputType::Down:
        return "Down";
    case EInputType::DownLeft:
        return "DownLeft";
    case EInputType::Left:
        return "Left";
    case EInputType::TopLeft:
        return "TopLeft";
    case EInputType::LightPunch:
        return "LightPunch";
    case EInputType::MediumPunch:
        return "MediumPunch";
    case EInputType::HeavyPunch:
        return "HeavyPunch";
    case EInputType::LightKick:
        return "LightKick";
    case EInputType::MediumKick:
        return "MediumKick";
    case EInputType::HeavyKick:
        return "HeavyKick";
    default:
        return "None";
    }
}

EInputType InputFromString(FString string)
{
    if (string == "None")
        return EInputType::None;
    if (string == "Top")
        return EInputType::Top;
    if (string == "TopRight")
        return EInputType::TopRight;
    if (string == "Right")
        return EInputType::Right;
    if (string == "DownRight")
        return EInputType::DownRight;
    if (string == "Down")
        return EInputType::Down;
    if (string == "DownLeft")
        return EInputType::DownLeft;
    if (string == "Left")
        return EInputType::Left;
    if (string == "TopLeft")
        return EInputType::TopLeft;
    if (string == "LightPunch")
        return EInputType::LightPunch;
    if (string == "MediumPunch")
        return EInputType::MediumPunch;
    if (string == "LightPunch")
        return EInputType::LightPunch;
    if (string == "MediumPunch")
        return EInputType::MediumPunch;
    if (string == "HeavyPunch")
        return EInputType::HeavyPunch;
    if (string == "LightKick")
        return EInputType::LightKick;
    if (string == "MediumKick")
        return EInputType::MediumKick;
    if (string == "HeavyKick")
        return EInputType::HeavyKick;

    return EInputType::None;
}

UInputBuffer::UInputBuffer()
{
}

UInputBuffer::UInputBuffer(TArray<UMotionInput*>& inputs)
{
    MotionInputs = inputs;

    /*UEnhancedInputLocalPlayerSubsystem sus;

    sus.GetPlayerInput()->ActionMappings[0].*/

    //UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    //InputBufferItem* item = new InputBufferItem();

    ////Input->BindAction(inputActions[0], ETriggerEvent::Triggered, item, &InputBufferItem::InputCheck);

    //m_MotionInputs = inputs;

    //Initialize();

    //m_ControlInputs->GetPlayerInput()->ActionMappings[0].Key = FKey::press

}

UInputBuffer::~UInputBuffer()
{
}

void UInputBuffer::add(TArray<UMotionInput*>& inputs)
{
    MotionInputs = inputs;

    /*UEnhancedInputLocalPlayerSubsystem sus;

    sus.GetPlayerInput()->ActionMappings[0].*/

    //UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    //InputBufferItem* item = new InputBufferItem();

    ////Input->BindAction(inputActions[0], ETriggerEvent::Triggered, item, &InputBufferItem::InputCheck);

    //m_MotionInputs = inputs;

    //Initialize();

    //m_ControlInputs->GetPlayerInput()->ActionMappings[0].Key = FKey::press

}

void UInputBuffer::Initialize()
{
    //m_InputBufferItems.Empty();

    //for(int i = 0; i < m_ControlInputs->GetPlayerInput()->ActionMappings.Num(); i++)
    //{
    //   /* InputBufferItem* item = new InputBufferItem();

    //    item->AssignButton(m_ControlInputs->GetPlayerInput()->ActionMappings[i]);

    //    m_InputBufferItems.push_back(item);*/
    //}
}

void UInputBuffer::BufferUpdate()
{
    GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::FromInt(InputBufferItems.Num()));
    if (InputBufferItems.Num() > 0) 
    {
       /* for(int i = 0; i < m_InputBufferItems.Num(); i++)
        {
            m_InputBufferItems[i]->InputCheck();
        }*/

        for (auto bufferItem : InputBufferItems)
        {
            // Checks if one of the buttons is pressed
            bufferItem->InputCheck();

            // This reads the buffer in reverse
            //for(int i = 0; i < bufferItem.Buffer.Count - 1; i++)
            //{
            //    // Moves the buffer data higher
            //    bufferItem.SetHoldUsed(i, bufferItem.Buffer[i + 1].HoldTime, bufferItem.Buffer[i + 1].IsUsed);

            for (int i = bufferItem->Buffer.Num() - 1; i > 0; i--)
            {
                // Moves the buffer data higher
                bufferItem->SetHoldUsed(i, bufferItem->Buffer[i - 1].HoldTime, bufferItem->Buffer[i - 1].IsUsed, bufferItem->Buffer[i - 1].MotionUsed);
            }

            if (bufferItem->InputDirection == EInputType::Left)
            {
                //GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::FromInt(bufferItem->m_Buffer[0].m_HoldTime));
            }
        }
    }
}

void UInputBuffer::UpdateMotion(bool right)
{
    for (int i = 0; i < MotionInputs.Num(); i++)
    {
        MotionInputs[i]->BufferCheck();

        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::FromInt(i));

        for (int j = 0; j < InputBufferItems.Num(); j++)
        {
            bool inputPressed = 0;
            int index = -1;

            EInputType direction = EInputType::None;

            if (InputBufferItems[j]->Buffer.Num() > 0)
            {
                for(int k = 0; k < InputBufferItems[j]->Buffer.Num(); k++)
                {
                    if (InputBufferItems[j]->Buffer[k].CanMotionExecute())
                    {
                        switch (InputBufferItems[j]->InputDirection)
                        {
                        case EInputType::Right:
                            if (right)
                                direction = EInputType::Right;
                            else if (!right)
                                direction = EInputType::Left;

                            inputPressed = 1;
                            index = k;
                            break;
                        case EInputType::Left:
                            if (right)
                                direction = EInputType::Left;
                            else if (!right)
                                direction = EInputType::Right;
                            inputPressed = 1;
                            index = k;
                            break;
                        case EInputType::LightPunch:
                            direction = EInputType::LightPunch;
                            inputPressed = 1;
                            index = k;
                            break;
                        case EInputType::MediumPunch:
                            direction = EInputType::MediumPunch;
                            inputPressed = 1;
                            index = k;
                            break;
                        case EInputType::HeavyPunch:
                            direction = EInputType::HeavyPunch;
                            inputPressed = 1;
                            index = k;
                            break;
                        }
                    }
                }
            }

            if (inputPressed && (index > -1) && (direction != EInputType::None))
                if (MotionInputs[i]->InputCheck(direction))
                    InputBufferItems[j]->Buffer[index].SetMotionTrue();
        }

        /*if (MotionInputs[i]->MotionComplete() == true)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Motion completed"));*/
    }
}

void UInputStateItem::HoldUp()
{
    if (HoldTime < 0)
    {
        HoldTime = 1;
    }
    else
    {
        HoldTime += 1;
    }
}

void UInputStateItem::ReleasedUp()
{
    if (HoldTime > 0)
    {
        HoldTime = -1;

        IsUsed = false;
        MotionUsed = false;
    }
    else
    {
        HoldTime = 0;
    }
}

void UInputStateItem::SetUsedTrue()
{
    IsUsed = true;
}

void UInputStateItem::SetMotionTrue()
{
    MotionUsed = true;
}

void UInputStateItem::SetHoldUsed(int time, bool used, bool motion)
{
    HoldTime = time;

    IsUsed = used;

    MotionUsed = motion;
}

bool UInputStateItem::CanExecute()
{
    if (HoldTime == 1 && !IsUsed)
    {
        return true;
    }

    return false;
}

bool UInputStateItem::CanMotionExecute()
{
    if (HoldTime == 1 && !MotionUsed)
    {
        return true;
    }

    return false;
}

UInputBufferItem::UInputBufferItem()
{
    for (int i = 0; i < 12; i++)
    {
        Buffer.Add(UInputStateItem());
    }
}

UInputBufferItem::UInputBufferItem(EInputType direction)
{
    InputDirection = direction;
}

void UInputBufferItem::AssignDirection(EInputType direction)
{
    InputDirection = direction;
}

void UInputBufferItem::InputCheck()
{
    if (Buffer.Num() > 0)
    {
        if (InputActionPressed)
        {
            Buffer[0].HoldUp();
        }
        else
        {
            Buffer[0].ReleasedUp();
        }
    }
}

void UInputBufferItem::SetUsedTrue()
{
    IsUsed = true;
}

void UInputBufferItem::SetUsedFalse()
{
    IsUsed = false;
}

void UInputBufferItem::SetInputActionPressed(bool pressed)
{
    InputActionPressed = pressed;

    if (pressed == 0)
        SetUsedFalse();
}

void UInputBufferItem::SetHoldUsed(int index, int time, bool used, bool motion)
{
    Buffer[index].SetHoldUsed(time, used, motion);
}

UMotionInput::UMotionInput()
{
}

UMotionInput::UMotionInput(TArray<EInputType> motions)
{
    MotionInputs = motions;
}

void UMotionInput::BufferCheck()
{
    if (IndexCheck > 0)
    {
        BufferTime++;

        if (BufferTime > 12)
            ResetInput();
    }
    else
        BufferTime = 0;
}

void UMotionInput::IncreaseIndex()
{
    IndexCheck++;

    BufferTime = 0;
}

void UMotionInput::ResetInput()
{
    IndexCheck = 0;

    BufferTime = 0;
}

bool UMotionInput::MotionComplete()
{
    if (IndexCheck >= MotionInputs.Num() && BufferTime <= 12)
    {
        BufferTime = 12;

        return true;
    }

    return false;
}

bool UMotionInput::InputCheck(EInputType input)
{
    if (IndexCheck < MotionInputs.Num())
    {
        if (MotionInputs[IndexCheck] == input)
        {
            IncreaseIndex();

            return true;
        }
    }

    return false;
}
