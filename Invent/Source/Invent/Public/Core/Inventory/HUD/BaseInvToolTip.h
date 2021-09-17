// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Inventory/BaseItem.h"
#include "Core/Inventory/BaseInventory.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "BaseInvToolTip.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API UBaseInvToolTip : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	//FSlotSignature SlotInfo;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	//int32 Amount;

	////meta = (BindWidget)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//UImage* ItemIconImage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* DescriptionTxtBlock;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* ItemNameTxtBlock;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* ItemTypeTxtBlock;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* AmountTxtBlock;

};
