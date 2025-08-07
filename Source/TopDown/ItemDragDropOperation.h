// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UItemDragDropOperation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	FIntPoint FromSlotPos = FIntPoint::ZeroValue;
	FVector2D DeltaWidgetPos = FVector2D::ZeroVector;


};
