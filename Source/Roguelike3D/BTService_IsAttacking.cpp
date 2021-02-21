#include "BTService_IsAttacking.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyBase.h"
#include "EnemyAIController.h"
#include "BlackboardKeys.h"

UBTService_IsAttacking::UBTService_IsAttacking()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Attacking");
}

void UBTService_IsAttacking::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	Super::OnBecomeRelevant(OwnerComp, node_memory);

	AEnemyAIController* const pEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyBase* const pEnemy = Cast<AEnemyBase>(pEnemyController->GetPawn());

	pEnemyController->GetBlackboard()->SetValueAsBool(bbKeys::is_attacking, pEnemy->GetEnemyState() == EEnemyState::Attack);
}