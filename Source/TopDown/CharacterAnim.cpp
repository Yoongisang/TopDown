// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayer.h"

UCharacterAnim::UCharacterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;

	}
}

void UCharacterAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Character = Cast<ACharacter>(Pawn);
		if (IsValid(Character))
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

void UCharacterAnim::AnimNotify_Hit()
{
	OnAttackHit.Broadcast();

}

void UCharacterAnim::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);
}

