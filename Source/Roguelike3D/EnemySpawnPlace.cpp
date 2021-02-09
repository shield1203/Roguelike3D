#include "EnemySpawnPlace.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Roguelike3DCharacter.h"

AEnemySpawnPlace::AEnemySpawnPlace()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnPlaceSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("EnemySpawnPlaceCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(500.f);
	m_collisionComponent->SetGenerateOverlapEvents(true);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawnPlace::OnPlayerInRange);

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EnemyspawnParticleComponent"));
	m_particleComponent->SetupAttachment(RootComponent);
}

void AEnemySpawnPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySpawnPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawnPlace::OnPlayerInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr)
	{
		
	}
}