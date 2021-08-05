// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Inventory/BaseItem.h"
#include "BaseInventory.generated.h"

USTRUCT(BlueprintType)
struct FSlotSignature
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Amount;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ABaseItem> Item;
};

UCLASS()
class INVENT_API ABaseInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInventory();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSlotSignature> Slots;
	



};
