// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "Core/Inventory/BaseInventory.h"
#include "InventGameMode.generated.h"

UCLASS(minimalapi)
class AInventGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AInventGameMode();

	

protected:

	virtual void BeginPlay() override;


};



