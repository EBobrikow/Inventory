// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ItemActorWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API UItemActorWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;

	UFUNCTION(BlueprintCallable)
		void SetItemName(bool isStackable, const FString& Name, int32 Amount);
};
