// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/ItemActorWidget.h"

void UItemActorWidget::SetItemName(bool isStackable, const FString& Name, int32 Amount)
{
	if (isStackable)
	{
		//FString string = FString::Printf(TEXT("Name = %s Mana = %d"), *Name, Amount);
		
		if(Amount > 1)
			ItemName->SetText(FText::FromString(FString::Printf(TEXT("%s x %i"), *Name, Amount)));
		else
			ItemName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Name)));

	}
	else
	{
		ItemName->SetText(FText::FromString(Name));
	}
}
