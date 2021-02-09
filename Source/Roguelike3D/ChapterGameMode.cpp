#include "ChapterGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Roguelike3DPlayerController.h"
#include "Roguelike3DCharacter.h"
#include "PortalSystem.h"
#include "ChapterAssetManager.h"
#include "BigmapManager.h"
#include "MinimapManager.h"
#include "Portal.h"

//
#include "Kismet/GameplayStatics.h"
#include "Inventory.h"
#include "EquipmentItem.h"

AChapterGameMode::AChapterGameMode()
{	
	PlayerControllerClass = ARoguelike3DPlayerController::StaticClass();
	m_curMapNumber = 0;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWidget(TEXT("/Game/Widgets/Chapter/WB_PlayerHUD"));
	if (PlayerWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), PlayerWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> BigmapWidget(TEXT("/Game/Widgets/Chapter/WB_Bigmap"));
	if (BigmapWidget.Succeeded())
	{
		m_bigmapWidget = CreateWidget(GetWorld(), BigmapWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryWidget(TEXT("/Game/Widgets/Chapter/WB_Inventory"));
	if (InventoryWidget.Succeeded())
	{
		m_inventoryWidget = CreateWidget(GetWorld(), InventoryWidget.Class);
	}
	m_flipInventory = false;

	m_portalSystem = CreateDefaultSubobject<UPortalSystem>(TEXT("GameMode_PortalSystem"));
	m_chapterAssetManager = CreateDefaultSubobject<UChapterAssetManager>(TEXT("GameMode_ChapterAssetManager"));
	m_bigmapManager = CreateDefaultSubobject<UBigmapManager>(TEXT("GameMode_BigmapManager"));
	m_minimapManager = CreateDefaultSubobject<UMinimapManager>(TEXT("GameMode_MinimapManager"));
}

void AChapterGameMode::StartPlay()
{
	Super::StartPlay();

	m_portalSystem->SetRandomRoguelikeMap();
	m_portalSystem->StartActivePortals(0);

	m_mainWidget->AddToViewport();

	// test
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		AEquipmentItem* item00 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item00->SetItemCode(EEquipmentItemCode::Blade);

		AEquipmentItem* item01 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item01->SetItemCode(EEquipmentItemCode::Screwdriver);

		AEquipmentItem* item02 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item02->SetItemCode(EEquipmentItemCode::Spanner);

		AEquipmentItem* item03 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item03->SetItemCode(EEquipmentItemCode::RedFloatRing);

		AEquipmentItem* item04 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item04->SetItemCode(EEquipmentItemCode::DuckFloatRing);

		AEquipmentItem* item05 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item05->SetItemCode(EEquipmentItemCode::RubbishBinLid);

		AEquipmentItem* item06 = pWorld->SpawnActor<AEquipmentItem>(FVector(0), FRotator(0), SpawnParams);
		item06->SetItemCode(EEquipmentItemCode::Ford);

		ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		pPlayerPawn->GetInventory()->AddItem(item00);
		pPlayerPawn->GetInventory()->AddItem(item01);
		pPlayerPawn->GetInventory()->AddItem(item02);
		pPlayerPawn->GetInventory()->AddItem(item03);
		pPlayerPawn->GetInventory()->AddItem(item04);
		pPlayerPawn->GetInventory()->AddItem(item05);
		pPlayerPawn->GetInventory()->AddItem(item06);
	}	
}

UChapterAssetManager* AChapterGameMode::GetChapterAssetManager() const
{
	return m_chapterAssetManager;
}

UBigmapManager* AChapterGameMode::GetBigmapManager() const
{
	return m_bigmapManager;
}

UMinimapManager* AChapterGameMode::GetMinimapManager() const
{
	return m_minimapManager;
}

void AChapterGameMode::SetCurMapNumber(int32 mapNumber, int32 xPos, int32 yPos)
{
	m_curMapNumber = mapNumber;

	m_bigmapManager->CheckVisitedBlocks(mapNumber, xPos, yPos);
}

int32 AChapterGameMode::GetCurMapNumber() const
{
	return m_curMapNumber;
}

void AChapterGameMode::VisibleBigmap(bool bVisibility)
{
	if (bVisibility)
	{
		m_bigmapWidget->AddToViewport();
	}
	else
	{
		m_bigmapWidget->RemoveFromViewport();
	}
}

void AChapterGameMode::FlipInventory()
{
	if (m_flipInventory)
	{
		m_inventoryWidget->RemoveFromViewport();
		m_flipInventory = false;
	}
	else
	{
		m_inventoryWidget->AddToViewport();
		m_flipInventory = true;
	}
}