// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/BaseInventory.h"

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
		FSlotSignature tmp = Slots[SlotNum1];
		Slots[SlotNum1] = Slots[SlotNum2];
		Slots[SlotNum2] = tmp;
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

// Called every frame
//void UBaseInventory::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

