// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Inventory/HUD/ItemActorWidget.h"
#include "Core/Inventory/BaseItem.h"
#include "Core/Inventory/BaseInventory.h"
#include "Kismet/GameplayStatics.h"
#include "BaseItemActor.generated.h"

UCLASS()
class INVENT_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemActorWidget* TitleWidget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMeshComponent;

	UPROPERTY( EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;

	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	//TSubclassOf<ABaseItem> Item;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	//int32 Amount;



};
