#include "GrimProjectile.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "PlayerProjectile.h"
#include "EnemyBase.h"
#include "EnemySpawnPlace.h"

AGrimProjectile::AGrimProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("GrimProjetileSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("GrimProjectileCollision"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(38.f);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGrimProjectile::OnProjectileBeginOverlap);
	m_collisionComponent->SetGenerateOverlapEvents(true);

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrimProjectileStaticMesh"));
	m_staticMeshComponent->SetupAttachment(m_collisionComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrimProjectileVisualAsset(TEXT("/Game/Blueprints/Enemy/Grim/SM_GrimProjectile"));
	if (GrimProjectileVisualAsset.Succeeded())
	{
		m_staticMeshComponent->SetStaticMesh(GrimProjectileVisualAsset.Object);
	}
	m_staticMeshComponent->SetRelativeLocation(FVector(0, 0, -34.f));

	m_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("GrimProjectileMovement"));
	m_projectileMovementComponent->SetUpdatedComponent(m_sceneCompoent);
	m_projectileMovementComponent->InitialSpeed = 2200.0f;
	m_projectileMovementComponent->MaxSpeed = 2200.0f;
	m_projectileMovementComponent->bRotationFollowsVelocity = true;
	m_projectileMovementComponent->ProjectileGravityScale = 0;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>GrimHitParticle(TEXT("/Game/ParagonGRIMexe/FX/Particles/Abilities/Primary/FX/P_GRIM_Primary_HitWorld"));
	if (GrimHitParticle.Succeeded())
	{
		m_particleSystem = GrimHitParticle.Object;
	}

	InitialLifeSpan = 5.0f;
}

void AGrimProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGrimProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrimProjectile::InitializeProjectile(const FVector& direction, float damageValue)
{
	m_damage = damageValue;

	m_projectileMovementComponent->Velocity = direction * m_projectileMovementComponent->InitialSpeed;
}

void AGrimProjectile::OnProjectileBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto pEnemyActor = Cast<AEnemyBase>(OtherActor);
	auto pGrimProjectile = Cast<AGrimProjectile>(OtherActor);
	auto pPlayerProjectile = Cast<APlayerProjectile>(OtherActor);
	auto pEnemySpawnPlace = Cast<AEnemySpawnPlace>(OtherActor);

	if (pEnemyActor || pGrimProjectile || pPlayerProjectile || pEnemySpawnPlace) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetActorLocation(), GetActorRotation());

	auto pPlayer = Cast<ARoguelike3DCharacter>(OtherActor);
	if (pPlayer)
	{

	}

	Destroy();
}