// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class TOPDOWN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	FVector CachedDestination;
	float FollowTime;
	bool bMousePressed = false;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UNiagaraSystem* FXCursor;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Click Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

private:

	AMyPlayerController();
protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:

	/** Input handlers */
	void OnInputStarted();

	void OnSetDestinationTriggered();

	void OnSetDestinationReleased();

};
