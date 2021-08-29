// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Inventory/BaseItem.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "BaseInventory.generated.h"

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
	// Sets default values for this actor's properties
	UBaseInventory();
	//virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	TArray<FSlotSignature> Slots;

	

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

private:

	UPROPERTY(EditAnywhere, Category = "Inventory params")
	int32 SlotsAmount;

	UPROPERTY(EditAnywhere, Category = "Inventory params")
	TEnumAsByte<EInventoryState> InventoryState;

	UPROPERTY(EditAnywhere, Category = "Inventory params")
	TEnumAsByte<EInventoryStartMode> StartMode;

protected:

	UPROPERTY()
	UBaseInventoryWidget* InventoryWidget;
};
