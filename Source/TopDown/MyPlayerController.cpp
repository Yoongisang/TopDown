// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"


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

void AMyPlayerController::OnInputStarted()
{
	StopMovement();

}

void AMyPlayerController::OnSetDestinationTriggered()
{
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
	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination);
	}

	FollowTime = 0.f;


}


