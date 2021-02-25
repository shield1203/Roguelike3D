#include "GrimAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy_Grim.h"

AGrimAIController::AGrimAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> GrimBehaviorTree(TEXT("BehaviorTree'/Game/Blueprints/Enemy/Grim/BT_Grim.BT_Grim'"));
	if (GrimBehaviorTree.Succeeded())
	{
		m_behaviorTree = GrimBehaviorTree.Object;
	}

	SetPerceptionSystem(800.f, 350.f);
}

//void AGrimAIController::PlayerTick(float DeltaTime)
//{
//	Super::PlayerTick(DeltaTime);
//
//	AEnemy_Grim* pEnemyPawn = Cast<AEnemy_Grim>(GetPawn());
//	if (pEnemyPawn && pEnemyPawn->GetEnemyState() == EEnemyState::Attack)
//	{
//		
//	}
//}

void AGrimAIController::Attack()
{
	AEnemy_Grim* pEnemyPawn = Cast<AEnemy_Grim>(GetPawn());
	if (pEnemyPawn)
	{
		pEnemyPawn->StartFire();
	}
}