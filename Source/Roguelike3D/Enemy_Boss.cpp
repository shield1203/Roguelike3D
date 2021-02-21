#include "Enemy_Boss.h"
#include "BossSkillObject.h"
#include "BossPojectile.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "BossAnimInstance.h"

AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	m_enemyCode = EEnemyCode::Boss;
	m_enemyState = EEnemyState::Attack;

	m_maxPattern = 3;
}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	LoadEnemyData();
}

void AEnemy_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_bossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	m_bossAnimInstance->OnPattrenA.BindUFunction(this, FName("PatternA"));
	m_bossAnimInstance->OnPattrenB.BindUFunction(this, FName("PatternB"));
	m_bossAnimInstance->OnPattrenC.BindUFunction(this, FName("PatternC"));
	m_bossAnimInstance->OnEnd.BindUFunction(this, FName("EndPattern"));
}

void AEnemy_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_enemyState == EEnemyState::Death) return;
	

}

void AEnemy_Boss::StartPattern()
{
	if (m_enemyState == EEnemyState::Attack) return;
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
	case 0: m_bossAnimInstance->StartPatternA(); break;
	case 1: m_bossAnimInstance->StartPatternB(); break;
	case 2: m_bossAnimInstance->StartPatternC(); break;
	}
}

void AEnemy_Boss::PatternA()
{
	UWorld* pWorld = GetWorld();

	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(pWorld, 0);

	FNavLocation randomLocation;
	UNavigationSystemV1* const pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (pWorld && pNavSystem->GetRandomPointInNavigableRadius(pPlayer->GetActorLocation(), 200.f, randomLocation, nullptr))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABossSkillObject* pObject = pWorld->SpawnActor<ABossSkillObject>(randomLocation.Location, FRotator(0), SpawnParams);
		if (pObject)
		{
			pObject->InitializeSkillObject(20.f, 2.f);
		}
	}
}

void AEnemy_Boss::PatternB()
{
	UWorld* pWorld = GetWorld();

	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(pWorld, 0);
	FVector playerLocation = pPlayer->GetActorLocation();

	float fRadian = FMath::Atan2(playerLocation.Y - GetActorLocation().Y, playerLocation.X - GetActorLocation().X);
	float fDegree = FMath::RadiansToDegrees(fRadian);

	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABossPojectile* pProjectile = pWorld->SpawnActor<ABossPojectile>(GetMesh()->GetSocketLocation(TEXT("projectileMuzzle")), FRotator(0, fDegree, 0), SpawnParams);
		if (pProjectile)
		{
			pProjectile->InitializeProjectile(FRotator(0, fDegree, 0).Vector(), m_enemyData.AttackPower);
		}
	}
}

void AEnemy_Boss::PatternC()
{

}

void AEnemy_Boss::EndPattern()
{
	m_enemyState = EEnemyState::Idle;
	UE_LOG(LogTemp, Warning, TEXT("EndPattern"));
}