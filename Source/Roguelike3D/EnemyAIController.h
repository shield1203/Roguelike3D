#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

UCLASS()
class ROGUELIKE3D_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "EnemyAI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* m_behaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "EnemyAI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* m_behaviorTree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "EnemyAI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* m_blackboardComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "EnemyAI", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* m_senseConfigSight;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* Pawn) override;

	virtual void Tick(float DeltaSeconds) override;

	void SetPerceptionSystem(float SightRadius, float VisionAngle);

public:
	AEnemyAIController();

	virtual void Attack() {};

	class UBlackboardComponent* GetBlackboard() const;

	void PlayerDetected();

	UFUNCTION(BlueprintCallable)
	void StopAI();

	UFUNCTION(BlueprintCallable)
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
};
