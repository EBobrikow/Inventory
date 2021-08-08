// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/BaseEnums.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENT_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseItem();
	~ABaseItem();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	TEnumAsByte<EItemTypes> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	UTexture2D* Icon2d;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	bool isStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item params")
	bool isUseble;
};
