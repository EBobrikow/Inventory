// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/Actors/BaseItemActor.h"

// Sets default values
ABaseItemActor::ABaseItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	RootComponent = BaseMeshComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("BaseMesh"));
	

}

// Called when the game starts or when spawned
void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();
	BaseMeshComponent->SetStaticMesh(BaseMesh);
}

// Called every frame
void ABaseItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

