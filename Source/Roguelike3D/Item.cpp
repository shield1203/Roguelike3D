#include "Item.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);

	m_collisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ItemCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetGenerateOverlapEvents(true);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

