// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

UCLASS()
class TOPDOWN_API ACreature : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking = false;
	UPROPERTY()
	class UCharacterAnim* CharacterAnim;
	UPROPERTY(BlueprintReadOnly)
	class UWidgetComponent* HpBar;
	UPROPERTY()
	class UCharacterInfo* CharacterInfo;

public:
	// Sets default values for this character's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Attack();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
public:
	virtual void OnAttackHit();
public:
	virtual void OnDead(AActor* DamageCauser) {};
};
