#include "BossPojectile.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "PlayerProjectile.h"
#include "EnemyBase.h"
#include "FloatingTextObject.h"

ABossPojectile::ABossPojectile()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("BossProjetileSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BossProjectileCollision"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(53.f);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossPojectile::OnProjectileBeginOverlap);
	m_collisionComponent->SetGenerateOverlapEvents(true);

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossProjectileStaticMesh"));
	m_staticMeshComponent->SetupAttachment(m_collisionComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrimProjectileVisualAsset(TEXT("/Game/Blueprints/Enemy/Boss/SM_BossProjectile"));
	if (GrimProjectileVisualAsset.Succeeded())
	{
		m_staticMeshComponent->SetStaticMesh(GrimProjectileVisualAsset.Object);
	}
	m_staticMeshComponent->SetRelativeLocation(FVector(0, 0, -50.f));

	m_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BossProjectileMovement"));
	m_projectileMovementComponent->SetUpdatedComponent(m_sceneCompoent);
	m_projectileMovementComponent->InitialSpeed = 900.0f;
	m_projectileMovementComponent->MaxSpeed = 900.0f;
	m_projectileMovementComponent->bRotationFollowsVelocity = true;
	m_projectileMovementComponent->ProjectileGravityScale = 0;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>GrimHitParticle(TEXT("/Game/ParagonRiktor/FX/Particles/Abilities/Hook/FX/P_Chains_Hook_HitWorld"));
	if (GrimHitParticle.Succeeded())
	{
		m_particleSystem = GrimHitParticle.Object;
	}

	InitialLifeSpan = 6.0f;
	
	m_hitCount = 2;
}

void ABossPojectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossPojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossPojectile::InitializeProjectile(const FVector& direction, float damageValue)
{
	m_damage = damageValue;

	m_projectileMovementComponent->Velocity = direction * m_projectileMovementComponent->InitialSpeed;
}

void ABossPojectile::OnProjectileBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto pEnemyActor = Cast<AEnemyBase>(OtherActor);
	auto pGrimProjectile = Cast<ABossPojectile>(OtherActor);
	if (pEnemyActor || pGrimProjectile) return;

	auto pPlayerProjectile = Cast<APlayerProjectile>(OtherActor);
	if (pPlayerProjectile)
	{
		m_hitCount--;

		if(m_hitCount > 0) return;
	}

	auto pPlayer = Cast<ARoguelike3DCharacter>(OtherActor);
	if (pPlayer)
	{
		pPlayer->TakeDamagePlayer(m_damage);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		auto pFloatingText = GetWorld()->SpawnActor<AFloatingTextObject>(GetActorLocation(), FRotator(0), SpawnParams);
		if (pFloatingText)
		{
			pFloatingText->InitializeDamageText(m_damage, 1, 0, 0);
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetActorLocation(), GetActorRotation(), FVector(2.0f));
	Destroy();
}