// Fill out your copyright notice in the Description page of Project Settings.


#include "HpBarUserWidget.h"
#include "CharacterInfo.h"
#include "Components/ProgressBar.h"

void UHpBarUserWidget::BindHp(UCharacterInfo* Info)
{
	CharacterInfo = Info;
	CharacterInfo->OnHpChanged.AddUObject(this, &UHpBarUserWidget::UpdateHp);

	UpdateHp();

}

void UHpBarUserWidget::UpdateHp()
{
	if (HP_Bar && CharacterInfo)
	{
		HP_Bar->SetPercent(CharacterInfo->GetHpRatio());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PB_Bar or CharacterInfo is null!"));
	}
}