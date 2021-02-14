#include "BTService_IsInRange.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackboardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyBase.h"
#include "EnemyAIController.h"

UBTService_IsInRange::UBTService_IsInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Range");
}

void UBTService_IsInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	Super::OnBecomeRelevant(OwnerComp, node_memory);

	AEnemyAIController* const pEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyBase* const pEnemy = Cast<AEnemyBase>(pEnemyController->GetPawn());
	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	pEnemyController->GetBlackboard()->SetValueAsBool(bbKeys::is_In_range, pEnemy->GetDistanceTo(pPlayer) <= pEnemy->GetAttackRange());
}
