// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/BaseSlotWidget.h"


void UBaseSlotWidget::NativeConstruct()
{
    // Call the Blueprint "Event Construct" node
    Super::NativeConstruct();

 
}

void UBaseSlotWidget::UpdateSlotAmount()
{
    if (SlotAmountTxtCombo)
    {
        SlotAmountTxtCombo->SetText(FText::FromString(FString::FromInt(SlotAmount)));
    }
}
