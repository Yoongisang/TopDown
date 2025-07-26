// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemy.h"
#include "MyPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


AMyPlayerController::AMyPlayerController()
{
	//마우스 커서 보이게 설정
	bShowMouseCursor = true;
	//기본 마우스 커서 모양 설정
	DefaultMouseCursor = EMouseCursor::Default;

	//월드좌표 시작점
	CachedDestination = FVector::ZeroVector;

	//0으로 초기화
	FollowTime = 0.f;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MyPlayer = Cast<AMyPlayer>(GetPawn());


	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMyPlayerController::OnSetDestinationReleased);
	}

}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CheckCursorTrace();
	FollowAndAttack();
}

void AMyPlayerController::OnInputStarted()
{
	
	TargetActor = PointActor;
	bMousePressed = true;
	StopMovement();
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	FHitResult Hit;

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
	{
		CachedDestination = Hit.Location;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);

	}

}

void AMyPlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	if (FollowTime <= ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination);
		}

	}

	FollowTime = 0.f;


}

void AMyPlayerController::CheckCursorTrace()
{
	if (bMousePressed)
		return;

	FHitResult Hit;

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
	{
		auto Other = Cast<AEnemy>(Hit.GetActor());
		if (Other == nullptr)
		{
			if (PointActor)
			{
				PointActor->Unhighlight();
			}
		}
		else
		{
			if (PointActor)
			{
				if (PointActor != Other)
				{
					PointActor->Unhighlight();
					Other->Highlight();
				}

			}
			else
			{
				Other->Highlight();
			}
		}

		PointActor = Other;

	}
}

void AMyPlayerController::FollowAndAttack()
{
	if (TargetActor == nullptr)
		return;


	FVector Direction = TargetActor->GetActorLocation() - MyPlayer->GetActorLocation();
	float distance = Direction.Size2D();

	if (distance < 250.f)
	{
		if (bMousePressed)
		{
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MyPlayer->GetActorLocation(), TargetActor->GetActorLocation());
			MyPlayer->SetActorRotation(LookAtRotation);

			if (AttackMontage)
			{
				UGameplayStatics::ApplyDamage(TargetActor, 10.f, this, nullptr, NULL);
				GetCharacter()->PlayAnimMontage(AttackMontage);
			}

			TargetActor = PointActor;
		}
		else
		{
			TargetActor = nullptr;
		}

	}
	else
	{
		FVector WorldDirection = Direction.GetSafeNormal();
		MyPlayer->AddMovementInput(WorldDirection, 1.0, false);
	}

}


