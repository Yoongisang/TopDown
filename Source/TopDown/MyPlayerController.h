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

protected:
	UPROPERTY(BlueprintReadOnly)
	class AMyPlayer* MyPlayer;

	UPROPERTY(BlueprintReadOnly)
	class AEnemy* PointActor;

	UPROPERTY(BlueprintReadOnly)
	class AEnemy* TargetActor;
	
	//UPROPERTY(EditAnywhere)
	//class UAnimMontage* AttackMontage;

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

	virtual void PlayerTick(float DeltaTime) override; // Tick 추가

protected:

	/** Input handlers */
	void OnInputStarted();

	void OnSetDestinationTriggered();

	void OnSetDestinationReleased();

	

protected:

	void CheckCursorTrace();	//CursorTrace 추가

	void FollowAndAttack();

};
