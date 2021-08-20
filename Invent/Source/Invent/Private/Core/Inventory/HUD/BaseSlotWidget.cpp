// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/HUD/BaseSlotWidget.h"
#include "Blueprint/WidgetTree.h"


void UBaseSlotWidget::NativeConstruct()
{
    // Call the Blueprint "Event Construct" node
    Super::NativeConstruct();
   
 
}

void UBaseSlotWidget::UpdateSlotAmount()
{
    if (SlotAmountTxtCombo)
    {
        SlotAmountTxtCombo->SetText(FText::FromString(FString::FromInt(SlotAmount)));
    }
}

void UBaseSlotWidget::UpdateSlot()
{
   // SlotAmountTxtCombo = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()); //NewObject<UTextBlock>(UTextBlock::StaticClass());//CreateDefaultSubobject<UTextBlock>(TEXT("SlotTxtCombo"));
    ItemIcon = NewObject<UImage>(UImage::StaticClass()); // WidgetTree->ConstructWidget<UImage>(UImage::StaticClass);
    if (Inventory)
    {
        bool isEmpty = true;
        SlotInfo = Inventory->GetItemInfoByIndex(SlotIndex, isEmpty);
        if (isEmpty)
        {
            if (SlotAmountTxtCombo)
            {
                SlotAmountTxtCombo->SetVisibility(ESlateVisibility::Hidden); 
            }
               
           if (ItemIcon)           
               ItemIcon->SetVisibility(ESlateVisibility::Hidden);
            
        }
        else
        {
            if (SlotAmountTxtCombo && ItemIcon)
            {
                ItemIcon->SetBrushFromTexture(SlotInfo.Item->Icon2d);
                ItemIcon->SetVisibility(ESlateVisibility::Visible);
                if (!SlotInfo.Item->isStackable)
                {
                    SlotAmountTxtCombo->SetVisibility(ESlateVisibility::Hidden);
                }
                else
                {
                    SlotAmount = SlotInfo.Amount;
                    SlotAmountTxtCombo->SetText(FText::FromString(FString::FromInt(SlotAmount)));
                    SlotAmountTxtCombo->SetVisibility(ESlateVisibility::Visible);
                }
            }
           
        }
    }
    
}

bool UBaseSlotWidget::IsEmptySlot()
{
    return false;
}
