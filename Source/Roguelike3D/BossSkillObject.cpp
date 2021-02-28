#include "BossSkillObject.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "FloatingTextObject.h"

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

	static ConstructorHelpers::FObjectFinder<UParticleSystem>BossSkillObjectParticle(TEXT("/Game/ParagonRiktor/FX/Particles/Abilities/ShockingGround/FX/P_Chains_ShockingGround_Shockwave"));
	if (BossSkillObjectParticle.Succeeded())
	{
		m_particleSystem = BossSkillObjectParticle.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>BossObjectSound(TEXT("SoundCue'/Game/Resource/Sound/Boom_Cue.Boom_Cue'"));
	if (BossObjectSound.Succeeded())
	{
		m_soundCue = BossObjectSound.Object;
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
		break;
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_particleSystem, GetActorLocation(), GetActorRotation(), FVector(0.59f));
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), m_soundCue, GetActorLocation(), GetActorRotation());

	Destroy();
}