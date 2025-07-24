// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterAnim::UCharacterAnim()
{
}

void UCharacterAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Character = Cast<ACharacter>(Pawn);if (IsValid(Character))
		{
			MovementComponent = Character->GetCharacterMovement();
		}

	}
	
}

void UCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		Velocity = MovementComponent->Velocity;
		GroundSpeed = Velocity.Size2D();

		ShouldMove = GroundSpeed > 3.0f;
	}


}
