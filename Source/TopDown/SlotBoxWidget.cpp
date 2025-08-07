// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotBoxWidget.h"
#include "SlotWidget.h"
#include "ItemWidget.h"
#include "Components/UniformGridPanel.h"
#include "ItemDragDropOperation.h"

USlotBoxWidget::USlotBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<USlotWidget> SW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Slot.WBP_Slot_C'"));
	if (SW.Succeeded())
	{
		SlotWidgetClass = SW.Class;

	}

	ConstructorHelpers::FClassFinder<UItemWidget> IW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Item.WBP_Item_C'"));
	if (IW.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Item Widget"));
		ItemWidgetClass = IW.Class;
	}
}

void USlotBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	slotWidgets.SetNum(COLUMN * ROW);

	for (int x = 0; x < COLUMN; x++)
	{
		for (int y = 0; y < ROW; y++)
		{
			USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);

			int32 index = x * ROW + y;
			slotWidgets[index] = SlotWidget;
			GridPanel->AddChildToUniformGrid(SlotWidget, y, x);

		}
	}

	UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
	GridPanel->AddChildToUniformGrid(ItemWidget, 0, 0);

}

void USlotBoxWidget::InventoryItemChanged(const FIntPoint& ItemSlotPos)
{
}

void USlotBoxWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	UE_LOG(LogTemp, Log, TEXT("NativeOnDragLeave"));
}

bool USlotBoxWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	UE_LOG(LogTemp, Log, TEXT("NativeOnDragOver"));
	return false;
}

bool USlotBoxWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UItemDragDropOperation* DragDrop = Cast<UItemDragDropOperation>(InOperation);

	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;

	UE_LOG(LogTemp, Log, TEXT("X : %f, Y : %f"), ToWidgetPos.X, ToWidgetPos.Y);

	return false;
	
}

