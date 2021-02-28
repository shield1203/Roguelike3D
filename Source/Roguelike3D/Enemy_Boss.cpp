#include "Enemy_Boss.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "WidgetBase.h"
#include "BossSkillObject.h"
#include "BossPojectile.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "BossAnimInstance.h"
#include "BossAIController.h"
#include "ChapterGameMode.h"

AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UWidgetBase>BossHPBarWidget(TEXT("/Game/Widgets/Chapter/WB_BossHP"));
	if (BossHPBarWidget.Succeeded())
	{
		m_BossHPBarWidget = Cast<UWidgetBase>(CreateWidget(GetWorld(), BossHPBarWidget.Class));
	}

	m_enemyCode = EEnemyCode::Boss;
	m_enemyState = EEnemyState::Attack;

	m_maxPattern = 3;
}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	LoadEnemyData();

	m_BossHPBarWidget->SetOwningActor(this);
	m_BossHPBarWidget->AddToViewport();
}

void AEnemy_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_bossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	m_bossAnimInstance->OnPattrenA.BindUFunction(this, FName("PatternA"));
	m_bossAnimInstance->OnPattrenB.BindUFunction(this, FName("PatternB"));
	m_bossAnimInstance->OnPattrenC.BindUFunction(this, FName("PatternC"));
	m_bossAnimInstance->OnEnd.BindUFunction(this, FName("EndPattern"));
	m_bossAnimInstance->OnDeath.BindUFunction(this, FName("Death"));
}

void AEnemy_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_enemyState == EEnemyState::Death) return;
	

}

void AEnemy_Boss::TakeDamageEnemy(float Damage)
{
	Super::TakeDamageEnemy(Damage);

	if (m_enemyState == EEnemyState::Death) return;

	m_curHP -= Damage;
	if (m_curHP <= 0)
	{
		m_curHP = 0;
		StartDeath();
	}
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

	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector randomLocation = pPlayer->GetActorLocation();
		srand((unsigned int)time(0));
		randomLocation.X += (rand() % 200);
		randomLocation.Y += (rand() % 200);

		ABossSkillObject* pObject = pWorld->SpawnActor<ABossSkillObject>(randomLocation, FRotator(0), SpawnParams);
		if (pObject)
		{
			pObject->InitializeSkillObject(50.f, 2.f);
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
}

void AEnemy_Boss::StartDeath()
{
	m_enemyState = EEnemyState::Death;
	m_bossAnimInstance->StartDeath();

	ABossAIController* pController = Cast<ABossAIController>(GetController());
	if (pController) pController->StopAI();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemy_Boss::Death()
{
	m_BossHPBarWidget->RemoveFromViewport();

	AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (pGameMode)
	{
		pGameMode->SetChapterResult(true);
	}
}