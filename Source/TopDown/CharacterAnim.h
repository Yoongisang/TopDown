// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnim.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = "CharacterInfo", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector Velocity;
	UPROPERTY(Category = "CharacterInfo", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float GroundSpeed;
	UPROPERTY(Category = "CharacterInfo", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool ShouldMove;
	UPROPERTY(Category = "CharacterInfo", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool IsFalling;
public:
	UPROPERTY(VisibleAnywhere)
	class ACharacter* Character;
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* MovementComponent;
public:
	UCharacterAnim();
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
