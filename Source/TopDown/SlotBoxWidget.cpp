// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotBoxWidget.h"
#include "SlotWidget.h"
#include "ItemWidget.h"
#include "Components/UniformGridPanel.h"

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

	UE_LOG(LogTemp, Log, TEXT("NativeConstruct"));

	const int COLUMN = 4;
	const int ROW = 8;

	//slotWidgets.SetNum(32);
	slotWidgets.SetNum(COLUMN * ROW);

	for (int x = 0; x < COLUMN; x++)
	{
		for (int y = 0; y < ROW; y++)
		{
			USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);

			int32 index = x * ROW + y;
			UE_LOG(LogTemp, Log, TEXT("Index : %d"), index);
			slotWidgets[index] = SlotWidget;
			GridPanel->AddChildToUniformGrid(SlotWidget, y, x);

		}
	}

	UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
	GridPanel->AddChildToUniformGrid(ItemWidget, 0, 0);

}
