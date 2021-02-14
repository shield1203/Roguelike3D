#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsInRange.generated.h"

UCLASS()
class ROGUELIKE3D_API UBTService_IsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_IsInRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory) override;
};
