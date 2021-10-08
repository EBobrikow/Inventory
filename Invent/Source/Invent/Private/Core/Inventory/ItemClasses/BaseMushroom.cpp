// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ItemClasses/BaseMushroom.h"

void ABaseMushroom::UseBaseItem()
{
	UE_LOG(LogTemp,Warning,TEXT("Mushroom was used!"));
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TEXT("Mushroom was used!"));
}