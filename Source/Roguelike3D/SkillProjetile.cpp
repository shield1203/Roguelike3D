#include "SkillProjetile.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBase.h"

ASkillProjetile::ASkillProjetile()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("SkillProjectileSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SkillProjectileCollision"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(15.f);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASkillProjetile::OnProjectileBeginOverlap);
	m_collisionComponent->SetGenerateOverlapEvents(true);

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkillProjectileStaticMesh"));
	m_staticMeshComponent->SetupAttachment(m_collisionComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SkillProjectileVisualAsset(TEXT("/Game/PolygonCity/Meshes/Props/SM_Prop_Soda"));
	if (SkillProjectileVisualAsset.Succeeded())
	{
		m_staticMeshComponent->SetStaticMesh(SkillProjectileVisualAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>SkillProjectileMaterial(TEXT("/Game/Resource/MT_SkillProjectile"));
	if (SkillProjectileMaterial.Succeeded())
	{
		m_staticMeshComponent->SetMaterial(0, SkillProjectileMaterial.Object);
	}

	m_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SkillProjectileMovement"));
	m_projectileMovementComponent->SetUpdatedComponent(m_sceneCompoent);
	m_projectileMovementComponent->InitialSpeed = 1300.0f;
	m_projectileMovementComponent->MaxSpeed = 1300.0f;
	m_projectileMovementComponent->bRotationFollowsVelocity = true;
	m_projectileMovementComponent->ProjectileGravityScale = 0;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>SkillHitParticle(TEXT("/Game/ParagonGadget/FX/Abilities/Ultimate/FX/P_Turret_DamageFX"));
	if (SkillHitParticle.Succeeded())
	{
		m_particleSystem = SkillHitParticle.Object;
	}

	InitialLifeSpan = 3.0f;
}

void ASkillProjetile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillProjetile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillProjetile::InitializeProjectile(const FVector& direction, float damageValue)
{
	m_damage = damageValue;

	m_projectileMovementComponent->Velocity = direction * m_projectileMovementComponent->InitialSpeed;
}

void ASkillProjetile::OnProjectileBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* pEnemy = Cast<AEnemyBase>(OtherActor);
	if (!pEnemy) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetActorLocation(), GetActorRotation());
}