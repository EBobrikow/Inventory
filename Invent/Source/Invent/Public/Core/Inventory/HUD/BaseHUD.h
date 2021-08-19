// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Core/Inventory/HUD/BaseInventoryWidget.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void InitInventoryWidget(AInventCharacter* Character);

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
		UBaseInventoryWidget* InventoryWidget;
};
