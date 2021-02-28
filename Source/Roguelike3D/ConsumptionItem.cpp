#include "ConsumptionItem.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "ChapterAssetManager.h"
#include "ChapterGameMode.h"
#include "Roguelike3DCharacter.h"
#include "Inventory.h"
#include "FloatingTextObject.h"

AConsumptionItem::AConsumptionItem()
{
	PrimaryActorTick.bCanEverTick = true;

	m_use = false;

	m_collisionComponent->SetCollisionProfileName(TEXT("Item"));
	m_collisionComponent->SetSimulatePhysics(true);
	m_collisionComponent->BodyInstance.bLockXRotation = true;
	m_collisionComponent->BodyInstance.bLockYRotation = true;
	m_collisionComponent->SetBoxExtent(FVector(45.f, 45.f, 90.f));
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AConsumptionItem::OnPlayerBeginOverlap);

	m_staticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AConsumptionItem::BeginPlay()
{
	Super::BeginPlay();

	srand((unsigned int)time(0));
	int32 nImpulseValueX = (rand() % 800) - 400;
	int32 nImpulseValueY = (rand() % 800) - 400;
	m_collisionComponent->AddImpulse(FVector(nImpulseValueX, nImpulseValueY, 400), NAME_None, true);
}

void AConsumptionItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_staticMeshComponent->AddRelativeRotation(FRotator(0, 3.f, 0));
	m_staticMeshComponent->AddRelativeLocation(FVector(0, 0, sin(GetGameTimeSinceCreation())));
}

void AConsumptionItem::SetItemCode(EConsumptionItemCode itemCode)
{
	m_itemCode = itemCode;

	LoadItemData();
}

void AConsumptionItem::LoadItemData()
{
	m_itemData.ItemCode = m_itemCode;

	UDataTable* pItemDataTable = LoadObject<UDataTable>(this, TEXT("/Game/DataTable/ConsumptionItem"));
	//FConsumptionItemData* pItemData = pItemDataTable->FindRow<FConsumptionItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_itemData.ItemCode)))), FString(""));
	FConsumptionItemData* pItemData = pItemDataTable->FindRow<FConsumptionItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_itemCode)))), FString(""));
	m_itemData.Value = pItemData->Value;
	m_itemData.Target = pItemData->Target;
	m_itemData.R = pItemData->R;
	m_itemData.G = pItemData->G;
	m_itemData.B = pItemData->B;

	if (m_itemData.ItemCode == EConsumptionItemCode::Coin)
	{
		srand((unsigned int)time(0));
		m_itemData.Value = (rand() % 100) + 1;
	}

	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			m_staticMeshComponent->SetStaticMesh(pGameMode->GetChapterAssetManager()->GetConsumptionItemMesh(static_cast<uint8>(m_itemData.ItemCode)));
		}
	}
}

void AConsumptionItem::OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr && !m_use)
	{
		Use(pPlayerPawn);

		m_staticMeshComponent->SetVisibility(false);
		m_collisionComponent->SetSimulatePhysics(false);
		m_collisionComponent->SetCollisionProfileName(TEXT("NoCollision"));
		m_collisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		auto pFloatingText = GetWorld()->SpawnActor<AFloatingTextObject>(m_staticMeshComponent->GetComponentLocation(), FRotator(0), SpawnParams);
		if (pFloatingText)
		{
			pFloatingText->InitializeConsumptionText(m_itemData.Value, m_itemData.Target, m_itemData.R, m_itemData.G, m_itemData.B);
		}

		Destroy();
	}
}

void AConsumptionItem::Use(ARoguelike3DCharacter* pPlayerPawn)
{
	m_use = true;

	switch (m_itemCode)
	{
	case EConsumptionItemCode::Coin: pPlayerPawn->GetInventory()->ObtainCoin(m_itemData.Value); break;
	case EConsumptionItemCode::Milkshake:
	case EConsumptionItemCode::Donut: pPlayerPawn->RecoveryHP(m_itemData.Value); break;
	}
}