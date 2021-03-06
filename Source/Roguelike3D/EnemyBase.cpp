#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ChapterGameMode.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	m_enemyState = EEnemyState::Idle;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	m_HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHPBarWidgetComponent"));
	m_HPBarWidgetComponent->SetupAttachment(RootComponent);
	m_HPBarWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	m_particleSystem = nullptr;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::TakeDamageEnemy(float Damage)
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Damage"), 0.2f);
	
	GetWorldTimerManager().SetTimer(m_damageTimerHandle, this, &AEnemyBase::DamageTimerFinished, 0.1f, false);
}

void AEnemyBase::DamageTimerFinished()
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Damage"), 0.0f);
}

void AEnemyBase::SetMapNumber(int32 mapNumber)
{
	m_mapNumber = mapNumber;
}

void AEnemyBase::SetEnemyState(EEnemyState state)
{
	m_enemyState = state;
}

void AEnemyBase::LoadEnemyData()
{
	m_enemyData.EnemyCode = m_enemyCode;

	UDataTable* pItemDataTable = LoadObject<UDataTable>(this, TEXT("/Game/DataTable/Enemy"));
	FEnemyData* pEnemyData = pItemDataTable->FindRow<FEnemyData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_enemyCode)))), FString(""));
	m_enemyData.MaxHP = pEnemyData->MaxHP;
	m_curHP = pEnemyData->MaxHP;
	m_enemyData.AttackPower = pEnemyData->AttackPower;
	m_enemyData.DefensivPower = pEnemyData->DefensivPower;
	m_enemyData.AttackSpeed = pEnemyData->AttackSpeed;
	m_enemyData.Speed = pEnemyData->Speed;
	m_enemyData.AttackRange = pEnemyData->AttackRange;
}

EEnemyState AEnemyBase::GetEnemyState() const
{
	return m_enemyState;
}

float AEnemyBase::GetAttackRange() const
{
	return m_enemyData.AttackRange;
}

float AEnemyBase::CurHPPercent() const
{
	return m_curHP / m_enemyData.MaxHP;
}

void AEnemyBase::RemoveEnemyCount()
{
	AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (pGameMode)
	{
		pGameMode->RemoveEnemy(m_mapNumber);
	}
}