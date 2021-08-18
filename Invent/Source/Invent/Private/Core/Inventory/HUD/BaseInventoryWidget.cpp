// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/BaseInventoryWidget.h"

void UBaseInventoryWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	SlotsPerRow = 5;
	GenerateSlotWidgets();
}

void UBaseInventoryWidget::GenerateSlotWidgets()
{
	SlotWidgetArray.Empty();
	Slot_Panel->ClearChildren();
	if (Inventory)
	{
		for (int32 i = 0; i < Inventory->Slots.Num(); i++)
		{
			UBaseSlotWidget* SlotPanel = CreateWidget<UBaseSlotWidget>(this, UBaseSlotWidget::StaticClass());// CreateWidget<UBaseSlotWidget>(TEXT("slot"));
			Slot_Panel->AddChildToUniformGrid(SlotPanel, GetRow(i, SlotsPerRow), GetColumn(i, SlotsPerRow));
			SlotWidgetArray.Add(SlotPanel);
			SlotPanel->UpdateSlot();
		}
	}
	
}

int32 UBaseInventoryWidget::GetRow(int32 Index, int32 SlPerRow) const
{

	return trunc(Index/ SlotsPerRow);
}

int32 UBaseInventoryWidget::GetColumn(int32 Index, int32 SlPerRow) const
{
	return trunc(Index % SlotsPerRow);
}
