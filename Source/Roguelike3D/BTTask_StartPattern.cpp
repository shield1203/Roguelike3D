#include "BTTask_StartPattern.h"
#include "BossAIController.h"

UBTTask_StartPattern::UBTTask_StartPattern(FObjectInitializer const& object_initializer)
{
    bNotifyTick = true;
    NodeName = TEXT("Start Pattern");
}

EBTNodeResult::Type UBTTask_StartPattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ABossAIController* const pBossController = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if (pBossController)
    {
        pBossController->StartPattern();
    }

    return EBTNodeResult::Succeeded;
}