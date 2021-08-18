// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Core/Inventory/BaseInventory.h"
#include "Components/Image.h"
#include "BaseSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API UBaseSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SlotAmountTxtCombo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(BlueprintReadWrite)
	int32 SlotAmount;

	UFUNCTION(BlueprintCallable)
	void UpdateSlotAmount();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FSlotSignature SlotInfo;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	ABaseInventory* Inventory;

	UFUNCTION(BlueprintCallable)
	void UpdateSlot();

	UFUNCTION(BlueprintCallable)
	bool IsEmptySlot();

	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTexture2D* ItemIcon;*/
	
};
