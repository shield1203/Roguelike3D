#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StartPattern.generated.h"

UCLASS()
class ROGUELIKE3D_API UBTTask_StartPattern : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_StartPattern(FObjectInitializer const& object_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};