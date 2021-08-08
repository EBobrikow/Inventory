// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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

	UPROPERTY(BlueprintReadWrite)
	int32 SlotAmount;

	UFUNCTION(BlueprintCallable)
	void UpdateSlotAmount();

	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTexture2D* ItemIcon;*/
	
};
