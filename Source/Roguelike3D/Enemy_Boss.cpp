#include "Enemy_Boss.h"
#include "BossAnimInstance.h"
#include "BossSkillObject.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"

AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	m_maxPattern = 3;
}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEnemy_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

void AEnemy_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_enemyState == EEnemyState::Death) return;
	

}

void AEnemy_Boss::StartPattern()
{
	m_enemyState = EEnemyState::Attack;

	srand((unsigned int)time(0));
	int32 randomPattern = rand() % m_maxPattern;
	if (m_curPattern == randomPattern)
	{
		randomPattern += 1;
		randomPattern %= m_maxPattern;
	}
	m_curPattern = randomPattern;

	switch (m_curPattern)
	{
	case 0: m_bossAnimInstance->StartPattern0(); break;
	case 1: m_bossAnimInstance->StartPattern1(); break;
	case 2: m_bossAnimInstance->StartPattern2(); break;
	}
}

void AEnemy_Boss::Pattern0()
{
	UWorld* pWorld = GetWorld();

	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(pWorld, 0);

	FNavLocation randomLocation;
	UNavigationSystemV1* const pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (pWorld && pNavSystem->GetRandomPointInNavigableRadius(pPlayer->GetActorLocation(), 500.f, randomLocation, nullptr))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		ABossSkillObject* pProjectile = pWorld->SpawnActor<ABossSkillObject>(randomLocation.Location, FRotator(0), SpawnParams);
		if (pProjectile)
		{
			pProjectile->InitializeSkillObject(20.f, 2.f);
		}
	}
}

void AEnemy_Boss::Pattern1()
{

}

void AEnemy_Boss::Pattern2()
{

}

void AEnemy_Boss::EndPattern()
{
	m_enemyState = EEnemyState::Idle;
}