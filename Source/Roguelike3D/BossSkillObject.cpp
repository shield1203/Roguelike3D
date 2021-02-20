#include "BossSkillObject.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"

ABossSkillObject::ABossSkillObject()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("BossSkillObjectSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BossSkillObjectCollision"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetSphereRadius(150.f);
	m_collisionComponent->SetGenerateOverlapEvents(true);

	m_decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("BossSkillObjectDecalComponent"));
	m_decalComponent->SetupAttachment(RootComponent);
	m_decalComponent->SetRelativeRotation(FRotator(270.f, 0.0f, 0.0f).Quaternion());
	m_decalComponent->DecalSize = FVector(100.0f, 200.0f, 200.0f);
	static ConstructorHelpers::FObjectFinder<UMaterial>CircleRangeMaterial(TEXT("Material'/Game/Resource/MT_CircleRange.MT_CircleRange'"));
	if (CircleRangeMaterial.Succeeded())
	{
		m_decalComponent->SetDecalMaterial(CircleRangeMaterial.Object);
	}
	m_rangeMaterial = m_decalComponent->CreateDynamicMaterialInstance();

	static ConstructorHelpers::FObjectFinder<UParticleSystem>BossSkillObjectParticle(TEXT("/Game/ParagonRiktor/FX/Particles/Abilities/Primary/FX/P_Chains_Melee_Impact"));
	if (BossSkillObjectParticle.Succeeded())
	{
		m_particleSystem = BossSkillObjectParticle.Object;
	}

	m_maxTime = 2.0f;
	m_leftTime = 2.0f;
	m_maxValue = 0.4f;
}

void ABossSkillObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossSkillObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProgressRange(m_leftTime / m_maxTime);
	if (m_leftTime < 0)
	{
		FinishedTimer();
	}

	m_leftTime -= DeltaTime;
}

void ABossSkillObject::InitializeSkillObject(float fDamage, float fMaxTime)
{
	m_damage = fDamage;
	m_leftTime = fMaxTime;
	m_maxTime = fMaxTime;
}

void ABossSkillObject::ProgressRange(float fProgressPercent)
{
	float fRangePercent = FMath::Lerp(0.1f, m_maxValue, fProgressPercent);

	m_rangeMaterial->SetScalarParameterValue(TEXT("InternalRadius"), fRangePercent);
}

void ABossSkillObject::FinishedTimer()
{
	TSet<AActor*>pOverlappingActors;
	m_collisionComponent->GetOverlappingActors(pOverlappingActors);

	for (auto overlappingActor : pOverlappingActors)
	{
		ARoguelike3DCharacter* pPlayer = Cast<ARoguelike3DCharacter>(overlappingActor);
		if (pPlayer)
		{
			//
			UE_LOG(LogTemp, Warning, TEXT("Hit!!"));
		}
		break;
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetActorLocation(), GetActorRotation(), FVector(5.0f));

	Destroy();
}