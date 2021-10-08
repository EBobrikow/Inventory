// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEnums.generated.h"

/**
 * 
 */
UENUM()
enum EItemTypes
{
	Unknown     UMETA(DisplayName = "Unknown item"),
	Quest       UMETA(DisplayName = "Quest item"),
	Useble      UMETA(DisplayName = "Useble item"),
	Craft       UMETA(DisplayName = "Craft item"),
	Weapon      UMETA(DisplayName = "Weapon item"),
	Armor       UMETA(DisplayName = "Armor item"),
};

UENUM()
enum EInventoryStartMode
{
	ZeroInited		   UMETA(DisplayName = "Inited as new inventory"),
	Loaded		       UMETA(DisplayName = "Loaded inventory"),
	
};

UENUM(BlueprintType)
enum EInventoryState 
{
	Closed					UMETA(DisplayName = "Closed state"),
	OpenFree				UMETA(DisplayName = "Open and free state"),
	DestroyItemWindow		UMETA(DisplayName = "Destroying item state"),
	DropItemWindow			UMETA(DisplayName = "Droping item state"),

};

UCLASS()
class INVENT_API UBaseEnums : public UObject
{
	GENERATED_BODY()
	
};
