#include "Item.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ChapterAssetManager.h"
#include "ChapterGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			m_staticMeshComponent->SetStaticMesh(pGameMode->GetChapterAssetManager()->GetItemMesh());
		}
	}
	//m_staticMeshComponent->SetStaticMesh();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

