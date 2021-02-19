#include "Enemy_Boss.h"
#include "BossAnimInstance.h"

AEnemy_Boss::AEnemy_Boss()
{
	m_skilling = true;
}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEnemy_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

void AEnemy_Boss::AnimNotify_SkillEnd()
{
	m_skilling = false;
}