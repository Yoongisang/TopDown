// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "Enemy.generated.h"

UCLASS()
class TOPDOWN_API AEnemy : public ACreature
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

public:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Highlight();
	void Unhighlight();

public:

	virtual void OnDead(AActor* DamageCauser) override;
};
