// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInfo.generated.h"

UENUM(BlueprintType)
enum class ECharacterStatus : uint8
{
	NONE,
	MOVING,
	ATTACK,
	DEATH,
};

DECLARE_MULTICAST_DELEGATE(FOnHpChanged)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWN_API UCharacterInfo : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterInfo();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterStatus Status = ECharacterStatus::NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp = 100;

public:
	FOnHpChanged OnHpChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	void UpdateHp(float DamageAmount);
	float GetHpRatio();
};
