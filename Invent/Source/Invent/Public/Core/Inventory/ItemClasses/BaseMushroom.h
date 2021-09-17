// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/BaseItem.h"
#include "BaseMushroom.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API ABaseMushroom : public ABaseItem
{
	GENERATED_BODY()

public:

	virtual void UseBaseItem() override;
	
};
