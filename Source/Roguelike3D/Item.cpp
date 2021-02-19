#include "Item.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetGenerateOverlapEvents(true);

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(m_collisionComponent);
	m_staticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}