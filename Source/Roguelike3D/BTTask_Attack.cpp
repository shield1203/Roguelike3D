#include "BTTask_Attack.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "BlackBoardKeys.h"

UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& object_initializer)
{
    bNotifyTick = true;
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* const pEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    FVector enamyLocation = pEnemyController->GetPawn()->GetActorLocation();

    ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    FVector playerLocation = pPlayer->GetActorLocation();

    float fRadian = FMath::Atan2(playerLocation.Y - enamyLocation.Y, playerLocation.X - enamyLocation.X);
    float fDegree = FMath::RadiansToDegrees(fRadian);

    pEnemyController->Attack();
    pEnemyController->StopMovement();
    pEnemyController->GetPawn()->SetActorRotation(FRotator(0, fDegree, 0));

    return EBTNodeResult::Succeeded;
}