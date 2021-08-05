// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEnums.generated.h"

/**
 * 
 */
UENUM()
enum ItemTypes
{
	Unknown     UMETA(DisplayName = "Unknown item"),
	Quest       UMETA(DisplayName = "Quest item"),
	Useble      UMETA(DisplayName = "Useble item"),
	Craft       UMETA(DisplayName = "Craft item"),
	Weapon      UMETA(DisplayName = "Weapon item"),
	Armor       UMETA(DisplayName = "Armor item"),
};

UCLASS()
class INVENT_API UBaseEnums : public UObject
{
	GENERATED_BODY()
	
};
