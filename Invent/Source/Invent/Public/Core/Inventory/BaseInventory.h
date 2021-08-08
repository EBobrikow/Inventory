// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Inventory/BaseItem.h"
#include "GameFramework/Character.h"
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
class INVENT_API ABaseInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInventory();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	TArray<FSlotSignature> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	int32 SlotsAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	TEnumAsByte<EInventoryState> InventoryState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory params", meta = (ExposeOnSpawn = "true"))
	TEnumAsByte<EInventoryStartMode> StartMode;

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
};
