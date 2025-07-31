// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInfo.h"

// Sets default values for this component's properties
UCharacterInfo::UCharacterInfo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UCharacterInfo::BeginPlay()
{
	Super::BeginPlay();

	Hp = MaxHp;
}

void UCharacterInfo::UpdateHp(float DamageAmount)
{
	Hp = FMath::Clamp(Hp - (int)DamageAmount, 0, MaxHp);

	OnHpChanged.Broadcast();

	if (Hp == 0)
	{
		Status = ECharacterStatus::DEATH;
	}
}

float UCharacterInfo::GetHpRatio()
{
	if (MaxHp == 0 || Hp == 0)
		return 0.0f;

	return (float)Hp / (float)MaxHp;
}
