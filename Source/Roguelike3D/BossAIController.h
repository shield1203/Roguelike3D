#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "BossAIController.generated.h"

UCLASS()
class ROGUELIKE3D_API ABossAIController : public AEnemyAIController
{
	GENERATED_BODY()
	
public:
	ABossAIController();

	void StartPattern();
};
