// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/BaseInventoryWidget.h"
#include "Blueprint/WidgetTree.h"

void UBaseInventoryWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	SlotsPerRow = 5;
	//GenerateSlotWidgets();

	FScriptDelegate OnClickDelegate;
	OnClickDelegate.BindUFunction(this, "CloseButtonClicked");
	Close_Button->OnClicked.AddUnique(OnClickDelegate);

}

void UBaseInventoryWidget::GenerateSlotWidgets()
{
	SlotWidgetArray.Empty();
	Slot_Panel->ClearChildren();
	if (Inventory)
	{
		for (int32 i = 0; i < Inventory->Slots.Num(); i++)
		{
			UBaseSlotWidget* SlotPanel = WidgetTree->ConstructWidget<UBaseSlotWidget>(BaseSlotWidgetClass);//CreateWidget<UBaseSlotWidget>(this, UBaseSlotWidget::StaticClass());// CreateWidget<UBaseSlotWidget>(TEXT("slot"));
			SlotPanel->Inventory = this->Inventory;
			SlotPanel->SlotIndex = i;
			Slot_Panel->AddChildToUniformGrid(SlotPanel, GetRow(i, 5), GetColumn(i, 5));
			SlotWidgetArray.Add(SlotPanel);
			SlotPanel->UpdateSlot();
		}
	}
	
}

int32 UBaseInventoryWidget::GetRow(int32 Index, int32 SlPerRow) const
{

	return trunc(Index/ SlPerRow);
}

int32 UBaseInventoryWidget::GetColumn(int32 Index, int32 SlPerRow) const
{
	return trunc(Index % SlPerRow);
}

void UBaseInventoryWidget::CloseButtonClicked()
{
	if (this->IsInViewport())
	{
		this->RemoveFromViewport();
	}

}
