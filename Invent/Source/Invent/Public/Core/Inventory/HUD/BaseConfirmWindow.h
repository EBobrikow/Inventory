// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Core/Inventory/BaseInventory.h"
#include "BaseConfirmWindow.generated.h"

class UBaseInventory;
/**
* 
 * 
 */
UCLASS()
class INVENT_API UBaseConfirmWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBaseInventory* InventReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Mode;
};
