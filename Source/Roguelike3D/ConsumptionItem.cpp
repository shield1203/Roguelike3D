#include "ConsumptionItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "ConsumptionItemWidget.h"
#include "ChapterAssetManager.h"
#include "ChapterGameMode.h"
#include "Roguelike3DCharacter.h"
#include "Inventory.h"

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

	m_valueWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ValueWidgetComponent"));
	m_valueWidget->SetupAttachment(m_collisionComponent);
	static ConstructorHelpers::FClassFinder<UConsumptionItemWidget> ValueWidget(TEXT("/Game/Widgets/Chapter/WB_ConsumptionValue"));
	if (ValueWidget.Succeeded())
	{
		m_valueWidget->SetWidgetClass(ValueWidget.Class);
	}
	m_valueWidget->SetWidgetSpace(EWidgetSpace::Screen);
	m_valueWidget->SetDrawSize(FVector2D(500.0f, 60.0f));
	m_valueWidget->RegisterComponent();
	m_valueWidget->SetVisibility(false);

	m_staticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AConsumptionItem::BeginPlay()
{
	Super::BeginPlay();

	LoadItemData();

	UConsumptionItemWidget* pValueWidget = Cast<UConsumptionItemWidget>(m_valueWidget->GetUserWidgetObject());
	if (pValueWidget)
	{
		pValueWidget->SetValue(this, m_itemData.Value, m_itemData.Target, m_itemData.R, m_itemData.G, m_itemData.B);
	}

	srand((unsigned int)time(0));
	int32 nImpulseValueX = (rand() % 800) - 400;
	int32 nImpulseValueY = (rand() % 800) - 400;
	m_collisionComponent->AddImpulse(FVector(nImpulseValueX, nImpulseValueY, 0), NAME_None, true);
}

void AConsumptionItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_staticMeshComponent->AddRelativeRotation(FRotator(0, 3.f, 0));
	m_staticMeshComponent->AddRelativeLocation(FVector(0, 0, sin(GetGameTimeSinceCreation())));
}

void AConsumptionItem::SetItemCode(EConsumptionItemCode itemCode)
{
	m_itemData.ItemCode = itemCode;
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
		m_itemData.Value = (rand() % 100) + 1;;
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
		m_valueWidget->SetVisibility(true);
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