// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Inventory/BaseInventory.h"
#include "BaseRecicle.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API UBaseRecicle : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBaseInventory* InventRef;
};
