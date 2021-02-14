#include "BTTask_ChasePlayer.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackboardKeys.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* const pEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	pEnemyController->GetBlackboard()->SetValueAsVector(bbKeys::target_location, pPlayer->GetActorLocation());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pEnemyController, pPlayer->GetActorLocation());

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
