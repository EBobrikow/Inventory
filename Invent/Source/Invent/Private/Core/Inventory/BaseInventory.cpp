// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/BaseInventory.h"
#include "Core/Inventory/HUD/BaseInventoryWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UBaseInventory::UBaseInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;
	Slots.Empty();
	//SlotsAmount = 10;
	//Init();
}

// Called when the game starts or when spawned
void UBaseInventory::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp,Warning,TEXT("Inited slots %i"),Slots.Num());
}

FSlotSignature UBaseInventory::GetItemInfoByIndex(int32 Index, bool& IsEmpty) const
{
	if (Slots.Num() > 0 && Index <= SlotsAmount)
	{
		if (Slots[Index].Item && Slots[Index].Amount > 0)
		{
			IsEmpty = false;
			return Slots[Index];
		}
		else
		{
			IsEmpty = true;
			return FSlotSignature();
		}
		
	}
	else
	{
		IsEmpty = true;
		return FSlotSignature();
	}
	
}

void UBaseInventory::Init()
{
	if (SlotsAmount > 0)
	{
		for (int32 i = 0; i < SlotsAmount; i++)
		{
			AddEmptySlot();
		}
	}
}

void UBaseInventory::AddEmptySlot()
{
	Slots.Add(FSlotSignature());
}

void UBaseInventory::AddItemToSlot(FSlotSignature Item, int32 SlotNum)
{
	if (SlotNum < SlotsAmount && SlotNum >= 0)
	{
		Slots[SlotNum] = Item;
	}
}

void UBaseInventory::SwapSlotContent(int32 SlotNum1, int32 SlotNum2)
{
	if (Slots.Num() > 0 && SlotNum1 <= SlotsAmount && SlotNum2 <= SlotsAmount)
	{
		/*FSlotSignature tmp = Slots[SlotNum1];
		Slots[SlotNum1] = Slots[SlotNum2];
		Slots[SlotNum2].Amount = tmp.Amount;
		Slots[SlotNum2].Item = tmp.Item;*/
		Swap(Slots[SlotNum1], Slots[SlotNum2]);
		UpdateWidgetSlot(SlotNum1);
		UpdateWidgetSlot(SlotNum2);
	}
}

void UBaseInventory::SetSlotsAmount(int32 Amount)
{
	SlotsAmount = Amount;
}

int32 UBaseInventory::GetSlotsAmount() const
{
	return SlotsAmount;
}

void UBaseInventory::SetInventoryState(EInventoryState State)
{
	InventoryState = State;
}

EInventoryState UBaseInventory::GetInventoryState() const
{
	return InventoryState;
}

void UBaseInventory::SetStartMode(EInventoryStartMode State)
{
	StartMode = State;
}

EInventoryStartMode UBaseInventory::GetStartMode() const
{
	return StartMode;
}

UBaseInventoryWidget* UBaseInventory::GetInventoryWidget() const
{
	if (InventoryWidget)
	{
		return InventoryWidget;
	}
	else
	{
		return nullptr;
	}
	
}

void UBaseInventory::SetInventoryWidget(UBaseInventoryWidget* invWidgetRef)
{
	if (invWidgetRef)
	{
		InventoryWidget = invWidgetRef;
	}
}

void UBaseInventory::UpdateWidgetSlot(int32 Index)
{
	InventoryWidget->SlotWidgetArray[Index]->UpdateSlot();
}

bool UBaseInventory::SearchEmptySlot(int32& Index)
{
	for (int32 i = 0; i<Slots.Num();i++)
	{
		if (!Slots[i].Item)
		{
			Index = i;
			return true;
		}
	}
	return false;
}

bool UBaseInventory::SearchSlotIndexForStack(TSubclassOf<ABaseItem> ItemCalssToSearch, int32& Index)
{
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].Item && Slots[i].Item->GetClass() == ItemCalssToSearch)
		{
			Index = i;
			return true;
		}
	}
	return false;
}

int32 UBaseInventory::AddItem(ABaseItem* ItemClass, int32 Amount, bool& Success) // result 1 - added to empty slot, 2 - stacked to existing slot, 3 - no place in inventory
{
	int32 SearchIndex = 0;
	if (Amount > 0)
	{
	
		//ABaseItem* locItem = Cast<ABaseItem>(ItemClass->GetDefaultObject());
		if (ItemClass->isStackable)
		{
			if (SearchSlotIndexForStack(ItemClass->GetClass(), SearchIndex))
			{
				Slots[SearchIndex].Amount += Amount;
				UpdateWidgetSlot(SearchIndex);
				Success = true;
				return 2;
			}
			else
			{
				if (SearchEmptySlot(SearchIndex))
				{
					FSlotSignature UpdSlot = FSlotSignature();
					UpdSlot.Amount = Amount;
					UpdSlot.Item = ItemClass;
					Slots[SearchIndex] = UpdSlot;
					UpdateWidgetSlot(SearchIndex);
					Success = true;
					return 1;
				}
				else
				{
					Success = false;
					return 3;
				}
			}
		}
		else
		{
			if (SearchEmptySlot(SearchIndex))
			{
				FSlotSignature UpdSlot = FSlotSignature();
				UpdSlot.Amount = Amount;
				UpdSlot.Item = ItemClass;
				Slots[SearchIndex] = UpdSlot;
				UpdateWidgetSlot(SearchIndex);
				Success = true;
				return 1;
			}
			else
			{
				Success = false;
				return 3;
			}
		}
	}
	else
	{
		Success = false;
		return 3;
	}
	
	Success = false;
	return 3;
}

void UBaseInventory::RemoveItemAtIndex(int32 Index, int32 Amount)
{
	if (Slots[Index].Amount <= Amount)
	{
		Slots[Index] = FSlotSignature();
		UpdateWidgetSlot(Index);
		return;
	}
	else
	{
		
		Slots[Index].Amount -= Amount;
		if (Slots[Index].Amount == 0)
		{
			Slots[Index] = FSlotSignature();
		}
		UpdateWidgetSlot(Index);
		return;
	}

}

int32 UBaseInventory::InvStateToInt(EInventoryState State)
{
	switch (State)
	{
	case Closed:
		return 1;
		break;
	case OpenFree:
		return 2;
		break;
	case DestroyItemWindow:
		return 3;
		break;
	case DropItemWindow:
		return 4;
		break;
	default:
		return 0;
		break;
	}
}

void UBaseInventory::UseItemAtIndex(int32 Index)
{
	
	if (InventoryState == EInventoryState::OpenFree)
	{
		Slots[Index].Item->UseBaseItem();
		RemoveItemAtIndex(Index,1);
	}
}

void UBaseInventory::InitConfWindow(bool WorkMode, int32 IndexOfDraggedSlot)
{
	//BaseRecicleClass
	/*if (BaseConfirmWindowClass)
	{*/
		BaseConfirmWindowRef = CreateWidget<UBaseConfirmWindow>(UGameplayStatics::GetPlayerController(GetWorld(), 0), BaseConfirmWindowClass);
		BaseConfirmWindowRef->InventReference = this;
		BaseConfirmWindowRef->Mode = WorkMode;
		BaseConfirmWindowRef->SlotIndex = IndexOfDraggedSlot;

	//}
}

void UBaseInventory::DestroyItemAtIndex(int32 Indx)
{
	int32 x = 0, y = 0;
	

		/*InitConfWindow(true, Indx);
		if (BaseConfirmWindowRef)
		{
			APlayerController* PlContr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlContr->GetViewportSize(x,y);
			BaseConfirmWindowRef->AddToViewport();
			BaseConfirmWindowRef->SetPositionInViewport(FVector2D(x/2,y/2));

		}*/

	Slots[Indx] = FSlotSignature();
	UpdateWidgetSlot(Indx);
	
}

void UBaseInventory::DestroyItemAtIndexNum(int32 Indx, int32 AmountToDel)
{
	if (AmountToDel >= Slots[Indx].Amount)
	{
		//Slots[Indx] = FSlotSignature();
		Slots.RemoveAt(Indx);
		AddEmptySlot();
	}
	else
	{
		Slots[Indx].Amount -= AmountToDel;
	}
	UpdateWidgetSlot(Indx);
	
}

void UBaseInventory::BroadcastDrop(int32 Index)
{
	DropDelegate.Broadcast(Index);

}



// Called every frame
//void UBaseInventory::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

