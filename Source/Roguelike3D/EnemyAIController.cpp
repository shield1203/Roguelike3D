#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "BlackBoardKeys.h"
#include "Roguelike3DCharacter.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	m_behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("EnemyBehaviorTreeComponent"));
	m_blackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("EnemyBlackboardComponent"));

	m_senseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfigSight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent")));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(m_behaviorTree);
	m_behaviorTreeComponent->StartTree(*m_behaviorTree);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyAIController::SetPerceptionSystem(float SightRadius, float VisionAngle)
{
	m_senseConfigSight->SightRadius = SightRadius; // 시야 범위
	m_senseConfigSight->LoseSightRadius = m_senseConfigSight->SightRadius + 100.f; // 시야를 벗어날 범위
	m_senseConfigSight->PeripheralVisionAngleDegrees = VisionAngle; // 시야각
	m_senseConfigSight->SetMaxAge(5.0f); // 감각 기억시간
	m_senseConfigSight->AutoSuccessRangeFromLastSeenLocation = 500.f;

	m_senseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	m_senseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	m_senseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*m_senseConfigSight->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*m_senseConfigSight);
}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto const player = Cast<ARoguelike3DCharacter>(Actor))
	{
		if (!GetBlackboard()->GetValueAsBool(bbKeys::can_see_player))
		{
			GetBlackboard()->SetValueAsBool(bbKeys::can_see_player, Stimulus.WasSuccessfullySensed());
		}
	}
}

UBlackboardComponent* AEnemyAIController::GetBlackboard() const
{
	return m_blackboardComponent;
}

void AEnemyAIController::PlayerDetected()
{
	GetBlackboard()->SetValueAsBool(bbKeys::can_see_player, true);
}

void AEnemyAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
