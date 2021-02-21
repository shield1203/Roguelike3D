#include "BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy_Boss.h"

ABossAIController::ABossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> GrimBehaviorTree(TEXT("BehaviorTree'/Game/Blueprints/Enemy/Boss/BT_Boss.BT_Boss'"));
	if (GrimBehaviorTree.Succeeded())
	{
		m_behaviorTree = GrimBehaviorTree.Object;
	}
}

void ABossAIController::StartPattern()
{
	AEnemy_Boss* pBossPawn = Cast<AEnemy_Boss>(GetPawn());
	if (pBossPawn)
	{
		pBossPawn->StartPattern();
	}
}