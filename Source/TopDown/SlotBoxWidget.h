// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotBoxWidget.generated.h"

/**
 * 
 */

class USlotWidget;
class UUniformGridPanel;

UCLASS()
class TOPDOWN_API USlotBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USlotBoxWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	virtual void NativeConstruct() override;
public:
	TSubclassOf<USlotWidget> SlotWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel;

};
