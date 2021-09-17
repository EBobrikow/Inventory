// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/BaseInventoryWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UBaseInventoryWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	SlotsPerRow = 5;
	//GenerateSlotWidgets();

	FScriptDelegate OnClickDelegate;
	OnClickDelegate.BindUFunction(this, "CloseOpenWidget");
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

void UBaseInventoryWidget::CloseOpenWidget()
{
	

	APlayerController* CharacterController = UGameplayStatics::GetPlayerController(this, 0);

	if (this->IsInViewport())
	{
		if (CharacterController)
		{
			CharacterController->SetInputMode(FInputModeGameOnly());
			CharacterController->bShowMouseCursor = false;
			CharacterController->bEnableClickEvents = false;
			CharacterController->bEnableMouseOverEvents = false;


		}

		Inventory->SetInventoryState(EInventoryState::Closed);
		this->RemoveFromViewport();


	}
	else
	{

		this->AddToViewport();
		//InventoryWidget->SetUserFocus(UGameplayStatics::GetPlayerController(this, 0));

		if (CharacterController)
		{
			CharacterController->SetInputMode(FInputModeGameAndUI());
			CharacterController->bShowMouseCursor = true;
			CharacterController->bEnableClickEvents = true;
			CharacterController->bEnableMouseOverEvents = true;


		}

		Inventory->SetInventoryState(EInventoryState::OpenFree);

	}


}

void UBaseInventoryWidget::InitRecicle()
{
	//BaseRecicleClass
	if (BaseRecicleClass)
	{
		RecicleRef = CreateWidget<UBaseRecicle>(this, BaseRecicleClass);
		RecicleRef->InventRef = Inventory;
	}

}
