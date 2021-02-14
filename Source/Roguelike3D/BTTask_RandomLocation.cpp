#include "BTTask_RandomLocation.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "EnemyAIController.h"
#include "BlackBoardKeys.h"

UBTTask_RandomLocation::UBTTask_RandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_RandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const pAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto const pEnemy = pAIController->GetPawn();

	FNavLocation randomLocation;

	UNavigationSystemV1* const pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (pNavSystem->GetRandomPointInNavigableRadius(pEnemy->GetActorLocation(), m_searchRadius, randomLocation, nullptr))
	{
		pAIController->GetBlackboard()->SetValueAsVector(bbKeys::target_location, randomLocation.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}