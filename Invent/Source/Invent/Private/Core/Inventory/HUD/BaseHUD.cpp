// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/BaseHUD.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Core/Actors/InventCharacter.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	/*if (InventoryWidgetClass)
	{
		InventoryWidget = Cast<UBaseInventoryWidget>(CreateWidget(GetWorld(), InventoryWidgetClass));
		InventoryWidget->SetPositionInViewport(FVector2D(900,200));
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}
	}
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventCharacter::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		AInventCharacter* Character = Cast<AInventCharacter>(FoundActors[0]);
		if (Character)
		{
			Character->SetInventoryWidgetRef(InventoryWidget);
			InventoryWidget->Inventory = Character->CharacterInventory;
		}
		
	}*/
}

void ABaseHUD::InitInventoryWidget(AInventCharacter* Character)
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = Cast<UBaseInventoryWidget>(CreateWidget(GetWorld(), InventoryWidgetClass));
		InventoryWidget->SetPositionInViewport(FVector2D(900,200));
		
		if (Character)
		{
			Character->SetInventoryWidgetRef(InventoryWidget);
			InventoryWidget->Inventory = Character->CharacterInventory;
			InventoryWidget->GenerateSlotWidgets();
		}
	}
	
	
	

	

	if (InventoryWidgetClass)
	{
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}
	}
}


void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}