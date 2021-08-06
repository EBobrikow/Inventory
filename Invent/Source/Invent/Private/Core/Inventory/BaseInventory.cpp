// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/BaseInventory.h"

// Sets default values
ABaseInventory::ABaseInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Slots.Empty();
	SlotsAmount = 10;
}

// Called when the game starts or when spawned
void ABaseInventory::BeginPlay()
{
	Super::BeginPlay();
	Init();
	UE_LOG(LogTemp,Warning,TEXT("Inited slots %i"),Slots.Num());
}

void ABaseInventory::Init()
{
	if (SlotsAmount > 0)
	{
		for (int32 i = 0; i < SlotsAmount; i++)
		{
			AddEmptySlot();
		}
	}
}

void ABaseInventory::AddEmptySlot()
{
	Slots.Add(FSlotSignature());
}

void ABaseInventory::AddItemToSlot(FSlotSignature Item, int32 SlotNum)
{
	if (SlotNum < SlotsAmount && SlotNum >= 0)
	{
		Slots[SlotNum] = Item;
	}
}

void ABaseInventory::SwapSlotContent(int32 SlotNum1, int32 SlotNum2)
{
	if (Slots.Num() > 0 && SlotNum1 <= SlotsAmount && SlotNum2 <= SlotsAmount)
	{
		FSlotSignature tmp = Slots[SlotNum1];
		Slots[SlotNum1] = Slots[SlotNum2];
		Slots[SlotNum2] = tmp;
	}
}

// Called every frame
void ABaseInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

