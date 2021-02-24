#include "Enemy_Grim.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GrimAnimInstance.h"
#include "EnemyAIController.h"
#include "GrimProjectile.h"

AEnemy_Grim::AEnemy_Grim()
{
	m_enemyCode = EEnemyCode::Grim_White;
	m_enemyState = EEnemyState::Idle;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = 170.f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.f, 0.0f);

	int32 MaterialIndex[7] = {0, 1, 3, 5, 6, 9, 10};
	for (auto Index : MaterialIndex)
	{
		GetMesh()->CreateDynamicMaterialInstance(Index);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>GrimDethParticle(TEXT("/Game/ParagonGRIMexe/FX/Particles/Abilities/BFG/FX/P_GRIM_BFG_Explosion"));
	if (GrimDethParticle.Succeeded())
	{
		m_particleSystem = GrimDethParticle.Object;
	}

	/*m_stimulusComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("GrimStimulusComponent"));
	m_stimulusComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
	m_stimulusComponent->RegisterWithPerceptionSystem();*/
}

void AEnemy_Grim::BeginPlay()
{
	Super::BeginPlay();

	LoadEnemyData();
}

void AEnemy_Grim::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_grimAnimInstance = Cast<UGrimAnimInstance>(GetMesh()->GetAnimInstance());
	m_grimAnimInstance->OnFire.BindUFunction(this, FName("Fire"));
	m_grimAnimInstance->OnDeath.BindUFunction(this, FName("Death"));
}

void AEnemy_Grim::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (m_enemyState == EEnemyState::Death) return;

	m_curHP -= Damage;
	if (m_curHP <= 0)
	{
		m_curHP = 0;
		StartDeath();
	}
}

void AEnemy_Grim::StartFire()
{
	m_enemyState = EEnemyState::Attack;
	m_grimAnimInstance->StartFire();
}

void AEnemy_Grim::Fire()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		AGrimProjectile* pProjectile = pWorld->SpawnActor<AGrimProjectile>(GetMesh()->GetSocketLocation(TEXT("Muzzle_01")), GetActorRotation(), SpawnParams);
		if (pProjectile)
		{
			pProjectile->InitializeProjectile(GetActorRotation().Vector(), m_enemyData.AttackPower);
		}
	}
}

void AEnemy_Grim::StartDeath()
{
	m_enemyState = EEnemyState::Death;
	m_grimAnimInstance->StartDeath();

	AEnemyAIController* pController = Cast<AEnemyAIController>(GetController());
	if (pController) pController->StopAI();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemy_Grim::Death()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetMesh()->GetSocketLocation(TEXT("spine_04")), GetActorRotation());
	Destroy();
}