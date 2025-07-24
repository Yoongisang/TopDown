// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindDestination.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindDestination::UBTTask_FindDestination()
{
	NodeName = TEXT("Find Destination");
}

EBTNodeResult::Type UBTTask_FindDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn != nullptr)
	{

		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (NavSystem != nullptr)
		{
			FVector OriginLocation = Pawn->GetActorLocation();
			float SearchRadius = 1000.0f; // Example radius
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomReachablePointInRadius(OriginLocation, SearchRadius, RandomLocation))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Destination"), RandomLocation);
				return EBTNodeResult::Succeeded;
			}
		}


	}

	return EBTNodeResult::Failed;
}