// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Core/Inventory/BaseInventory.h"
#include "Core/Inventory/HUD/BaseSlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "BaseInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API UBaseInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Slot_Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Close_Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UBaseInventory* Inventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBaseSlotWidget*> SlotWidgetArray;

	UFUNCTION(BlueprintCallable)
	void GenerateSlotWidgets();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotsPerRow;

	UFUNCTION(BlueprintCallable)
	int32 GetRow(int32 Index, int32 SlPerRow) const;

	UFUNCTION(BlueprintCallable)
	int32 GetColumn(int32 Index, int32 SlPerRow) const;

protected:

	UFUNCTION()
		void CloseButtonClicked();
};
