#include "EnemySpawnPlace.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Roguelike3DCharacter.h"
#include "EnemyBase.h"
#include "ChapterGameMode.h"
#include "ChapterAssetManager.h"

AEnemySpawnPlace::AEnemySpawnPlace()
{
	PrimaryActorTick.bCanEverTick = true;

	m_spawnEnemy = false;
	m_spawnFinished = false;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnPlaceSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("EnemySpawnPlaceCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(500.f);
	m_collisionComponent->SetGenerateOverlapEvents(true);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawnPlace::OnPlayerInRange);

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EnemyspawnParticleComponent"));
	m_particleComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EnemySpawnParticleAsset(TEXT("/Game/TandP/Teleportation/Particle/P_EnemySpawn"));
	if (EnemySpawnParticleAsset.Succeeded())
	{
		m_particleComponent->SetTemplate(EnemySpawnParticleAsset.Object);
	}
}

void AEnemySpawnPlace::BeginPlay()
{
	Super::BeginPlay();
	
	m_particleComponent->SetActive(false);
}

void AEnemySpawnPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawnPlace::OnPlayerInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr && !m_spawnEnemy)
	{
		m_spawnEnemy = true;
		GetWorldTimerManager().SetTimer(m_enemySpawnTimerHandle, this, &AEnemySpawnPlace::EnemySpawnFinished, 2.5f, true);

		UWorld* pWorld = GetWorld();
		if (pWorld)
		{
			AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
			if (pGameMode)
			{
				m_particleComponent->SetActive(true);
				m_collisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				pWorld->SpawnActor<AEnemyBase>(pGameMode->GetChapterAssetManager()->GetEnemyBlueprintClass(static_cast<uint8>(m_spawnEnemyCode)), GetActorLocation(), GetActorRotation(), SpawnParams);
			}
		}
	}
}

void AEnemySpawnPlace::EnemySpawnFinished()
{
	if (m_spawnFinished)
	{
		GetWorldTimerManager().ClearTimer(m_enemySpawnTimerHandle);
		Destroy();
	}
	else
	{
		m_spawnFinished = true;
		m_particleComponent->SetActive(false);
	}
}