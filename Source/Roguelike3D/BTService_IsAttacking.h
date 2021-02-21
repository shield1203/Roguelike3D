#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsAttacking.generated.h"

UCLASS()
class ROGUELIKE3D_API UBTService_IsAttacking : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_IsAttacking();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory) override;
};
