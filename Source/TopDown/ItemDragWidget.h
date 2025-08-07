// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDragWidget.generated.h"

/**
 * 
 */
class UImage;

UCLASS()
class TOPDOWN_API UItemDragWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
};
