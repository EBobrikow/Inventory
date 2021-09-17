// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Inventory/BaseItem.h"
#include "Core/Inventory/HUD/BaseConfirmWindow.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "BaseInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDropDelegate, int32,Index);

USTRUCT(BlueprintType)
struct FSlotSignature
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Amount;

	UPROPERTY(BlueprintReadWrite)
	ABaseItem* Item;
};

UCLASS()
class INVENT_API UBaseInventory : public UActorComponent
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FDropDelegate DropDelegate;

	// Sets default values for this actor's properties
	UBaseInventory();
	//virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	TArray<FSlotSignature> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseConfirmWindow> BaseConfirmWindowClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBaseConfirmWindow* BaseConfirmWindowRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	ACharacter* CharacterRef;
	
	UFUNCTION(BlueprintCallable)
	FSlotSignature GetItemInfoByIndex(int32 Index, bool& IsEmpty) const;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void AddEmptySlot();

	UFUNCTION(BlueprintCallable)
	void AddItemToSlot(FSlotSignature Item, int32 SlotNum);
	
	UFUNCTION(BlueprintCallable)
	void SwapSlotContent(int32 SlotNum1, int32 SlotNum2);

	UFUNCTION(BlueprintCallable)
	void SetSlotsAmount(int32 Amount);

	UFUNCTION(BlueprintCallable)
	int32 GetSlotsAmount() const;

	UFUNCTION(BlueprintCallable)
	void SetInventoryState(EInventoryState State);

	UFUNCTION(BlueprintCallable)
	EInventoryState GetInventoryState() const;

	UFUNCTION(BlueprintCallable)
	void SetStartMode(EInventoryStartMode State);

	UFUNCTION(BlueprintCallable)
	EInventoryStartMode GetStartMode() const;

	UFUNCTION(BlueprintCallable)
	UBaseInventoryWidget* GetInventoryWidget() const;

	UFUNCTION(BlueprintCallable)
	void SetInventoryWidget(UBaseInventoryWidget* invWidgetRef);

	UFUNCTION(BlueprintCallable)
	void UpdateWidgetSlot(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool SearchEmptySlot(int32& Index);

	UFUNCTION(BlueprintCallable)
	bool SearchSlotIndexForStack(TSubclassOf<ABaseItem> ItemCalssToSearch, int32& Index);

	UFUNCTION(BlueprintCallable)
	int32 AddItem(ABaseItem* ItemClass, int32 Amount, bool& Success);

	UFUNCTION(BlueprintCallable)
	void RemoveItemAtIndex(int32 Index, int32 Amount);

	UFUNCTION(BlueprintCallable)
	int32 InvStateToInt(EInventoryState State);

	UFUNCTION(BlueprintCallable)
	void UseItemAtIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void InitConfWindow(bool WorkMode, int32 IndexOfDraggedSlot);

	UFUNCTION(BlueprintCallable)
	void DestroyItemAtIndex(int32 Indx);

	UFUNCTION(BlueprintCallable)
	void DestroyItemAtIndexNum(int32 Indx, int32 AmountToDel);

	UFUNCTION(BlueprintCallable)
	void BroadcastDrop(int32 Index);


private:

	UPROPERTY(EditAnywhere, Category = "Inventory params")
	int32 SlotsAmount;

	

	UPROPERTY(EditAnywhere, Category = "Inventory params")
	TEnumAsByte<EInventoryStartMode> StartMode;

protected:

	UPROPERTY(EditAnywhere, Category = "Inventory params")
		TEnumAsByte<EInventoryState> InventoryState;

	UPROPERTY()
	UBaseInventoryWidget* InventoryWidget;
};
