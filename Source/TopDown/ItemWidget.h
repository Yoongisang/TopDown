// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UItemDragWidget;


UCLASS()
class TOPDOWN_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	FIntPoint CachedFromSlotPos = FIntPoint::ZeroValue;
	FVector2D dCachedDeltaWidgetPos = FVector2D::ZeroVector;
	int32 ItemCount = 0;

protected:

	UPROPERTY()
	TSubclassOf<UItemDragWidget> ItemDragWidgetClass;

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Hover;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;

public:

	UItemWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	virtual void NativeConstruct() override;

protected:

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;



};
