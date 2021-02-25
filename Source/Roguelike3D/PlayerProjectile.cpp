#include "PlayerProjectile.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "ChapterGameMode.h"
#include "Roguelike3DCharacter.h"
#include "EnemyBase.h"
#include "EnemySpawnPlace.h"
#include "Item.h"
#include "ChapterAssetManager.h"
#include "FloatingTextObject.h"

APlayerProjectile::APlayerProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerProjetileSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerProjectileCollision"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(13.f);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnProjectileBeginOverlap);
	m_collisionComponent->SetGenerateOverlapEvents(true);

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerProjectileStaticMesh"));
	m_staticMeshComponent->SetupAttachment(m_collisionComponent);

	m_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PlayerProjectileMovement"));
	m_projectileMovementComponent->SetUpdatedComponent(m_sceneCompoent);
	m_projectileMovementComponent->InitialSpeed = 2000.0f;
	m_projectileMovementComponent->MaxSpeed = 2000.0f;
	m_projectileMovementComponent->bRotationFollowsVelocity = true;
	m_projectileMovementComponent->ProjectileGravityScale = 0;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>HitParticle(TEXT("/Game/ParagonGadget/FX/Abilities/ElectroGate/FX/P_SpeedBuffActivate"));
	if (HitParticle.Succeeded())
	{
		m_particleSystem = HitParticle.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>PlayerProjectileMaterial(TEXT("Material'/Game/Resource/MT_itemProjectile.MT_itemProjectile'"));
	if (PlayerProjectileMaterial.Succeeded())
	{
		m_materialInstance = PlayerProjectileMaterial.Object;
	}

	InitialLifeSpan = 5.0f;
}

void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerProjectile::InitializePlayerProjectile(const FVector& direction, EEquipmentItemCode itemCode, float damageValue)
{
	m_itemCode = itemCode;
	m_damage = damageValue;

	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			m_staticMeshComponent->SetStaticMesh(pGameMode->GetChapterAssetManager()->GetEquipmentItemMesh(static_cast<uint8>(m_itemCode)));
			m_staticMeshComponent->SetMaterial(0, m_materialInstance);
		}
	}

	m_projectileMovementComponent->Velocity = direction * m_projectileMovementComponent->InitialSpeed;
}

void APlayerProjectile::OnProjectileBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARoguelike3DCharacter* pPlayer = Cast<ARoguelike3DCharacter>(OtherActor);
	AItem* pItem = Cast<AItem>(OtherActor);
	APlayerProjectile* pProjectile = Cast<APlayerProjectile>(OtherActor);
	auto pEnemySpawnPlace = Cast<AEnemySpawnPlace>(OtherActor);

	if (pPlayer || pItem || pProjectile || pEnemySpawnPlace) return;

	AEnemyBase* pEnemy = Cast<AEnemyBase>(OtherActor);
	if (pEnemy)
	{
		pEnemy->TakeDamageEnemy(m_damage);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		auto pFloatingText = GetWorld()->SpawnActor<AFloatingTextObject>(GetActorLocation(), FRotator(0), SpawnParams);
		if (pFloatingText)
		{
			pFloatingText->InitializeDamageText(m_damage, 1, 0, 0);
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetActorLocation(), GetActorRotation());

	Destroy();
}