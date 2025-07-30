// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
protected:
	UPROPERTY()
	class UBehaviorTree* BehaviorTree;
	UPROPERTY()
	class UBlackboardData* BlackboardData;
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;


};
