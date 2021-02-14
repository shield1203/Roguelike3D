#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "GrimAIController.generated.h"

UCLASS()
class ROGUELIKE3D_API AGrimAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	AGrimAIController();

	//virtual void PlayerTick(float DeltaTime) override;

	virtual void Attack();
};
