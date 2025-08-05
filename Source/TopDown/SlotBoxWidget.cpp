// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotBoxWidget.h"
#include "SlotWidget.h"

USlotBoxWidget::USlotBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<USlotWidget> SW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Slot.WBP_Slot_C'"));
	if (SW.Succeeded())
	{
		SlotWidget = SW.Class;
		UE_LOG(LogTemp, Log, TEXT("Set SlotWidget"));

	}
}

void USlotBoxWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("NativeConstruct"));
}
