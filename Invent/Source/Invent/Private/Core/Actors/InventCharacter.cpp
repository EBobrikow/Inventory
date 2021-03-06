// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Actors/InventCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Core/Inventory/HUD/BaseHUD.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

//////////////////////////////////////////////////////////////////////////
// AInventCharacter

AInventCharacter::AInventCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//Create Inventory Component
	CharacterInventory = CreateDefaultSubobject<UBaseInventory>(TEXT("InventoryComponent"));
	CharacterInventory->CharacterRef = this;
	CharacterInventory->SetSlotsAmount(20);//SlotsAmount = 20;
	CharacterInventory->Init();


	
	
}

void AInventCharacter::BeginPlay()
{
	Super::BeginPlay();

	ABaseHUD* hud = Cast<ABaseHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	hud->InitInventoryWidget(this);
	
	CharacterController = UGameplayStatics::GetPlayerController(this, 0);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AInventCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AInventCharacter::OpenCloseInventory);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AInventCharacter::PickUpItem);
	//PickUp

	PlayerInputComponent->BindAxis("MoveForward", this, &AInventCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInventCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AInventCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AInventCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AInventCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AInventCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AInventCharacter::OnResetVR);
}

UBaseInventory* AInventCharacter::GetCharacterInventory() const
{
	if (CharacterInventory)
	{
		return CharacterInventory;
	}
	else
	{
		return nullptr;
	}
	
}

void AInventCharacter::PickUpItem()
{
	int32 AddItemResult = 0;
	bool successRes = false;
	if(ItemsToPickUp.Num() > 0)
	if (ItemsToPickUp[0])
	{
		ABaseItem* LocItem = Cast<ABaseItem>(ItemsToPickUp[0]->Item->GetDefaultObject());
		AddItemResult = CharacterInventory->AddItem(LocItem, ItemsToPickUp[0]->Amount, successRes);
		switch (AddItemResult)
		{
		case 1: //added to empty slot
			ItemsToPickUp[0]->Destroy();
			break;
		case 2:	//stacked to existing slot
			ItemsToPickUp[0]->Destroy();
			break;
		case 3:	//no place in inventory
			break;
		default:
			break;
		}
	}
}

void AInventCharacter::OpenCloseInventory()
{
	switch (CharacterInventory->InventoryState)
	{
	case EInventoryState::DestroyItemWindow:

		break;
	case EInventoryState::Closed:
	case EInventoryState::OpenFree:
		if (CharacterInventory->GetInventoryWidget())
		{
			CharacterInventory->GetInventoryWidget()->CloseOpenWidget();
		}
		break;
	default:
		break;
	}
	
}


void AInventCharacter::OnResetVR()
{
	// If Invent is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Invent.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AInventCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AInventCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AInventCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AInventCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AInventCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AInventCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
