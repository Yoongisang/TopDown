// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Attackable.h"
#include "EnemyAIController.h"
#include "MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Attackable::UBTDecorator_Attackable()
{
	NodeName = TEXT("Attckable");
}

bool UBTDecorator_Attackable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return false;

	auto Target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (Target == nullptr)
		return false;

	if (Target->GetDistanceTo(Pawn) > 250.f)
		return false;


	return true;
}
