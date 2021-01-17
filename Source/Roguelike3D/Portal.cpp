#include "Portal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Roguelike3DCharacter.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	m_activation = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("PortalSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PortalVisualAsset(TEXT("/Game/TandP/Teleportation/Mesh/SM_Teleportation"));
	if (PortalVisualAsset.Succeeded())
	{
		m_staticMeshComponent->SetStaticMesh(PortalVisualAsset.Object);
	}

	m_collisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PortalCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticleComponent"));
	m_particleComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PortalParticleAsset(TEXT("/Game/TandP/Teleportation/Particle/P_Teleportation"));
	if (PortalParticleAsset.Succeeded())
	{
		m_particleComponent->SetTemplate(PortalParticleAsset.Object);
	}

	m_buttonWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PortalButtonComponent"));
	m_buttonWidgetComponent->SetupAttachment(RootComponent);

}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	m_particleComponent->SetActive(false);
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

