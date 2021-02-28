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
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
//
#include "Kismet/GameplayStatics.h"
#include "Inventory.h"
#include "EquipmentItem.h"

AChapterGameMode::AChapterGameMode()
{	
	m_curMapNumber = 0;
	m_chapterResult = false;

	PlayerControllerClass = ARoguelike3DPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Widget  /////////////
	static ConstructorHelpers::FClassFinder<UUserWidget>PlayerWidget(TEXT("/Game/Widgets/Chapter/WB_PlayerHUD"));
	if (PlayerWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), PlayerWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>BigmapWidget(TEXT("/Game/Widgets/Chapter/WB_Bigmap"));
	if (BigmapWidget.Succeeded())
	{
		m_bigmapWidget = CreateWidget(GetWorld(), BigmapWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>InventoryWidget(TEXT("/Game/Widgets/Chapter/WB_Inventory"));
	if (InventoryWidget.Succeeded())
	{
		m_inventoryWidget = CreateWidget(GetWorld(), InventoryWidget.Class);
	}
	m_flipInventory = false;

	static ConstructorHelpers::FClassFinder<UUserWidget>ChapterSuccessWidget(TEXT("/Game/Widgets/Chapter/WB_ChapterSuccess"));
	if (ChapterSuccessWidget.Succeeded())
	{
		m_successWidget = CreateWidget(GetWorld(), ChapterSuccessWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>ChapterFailWidget(TEXT("/Game/Widgets/Chapter/WB_ChapterFail"));
	if (ChapterFailWidget.Succeeded())
	{
		m_failWidget = CreateWidget(GetWorld(), ChapterFailWidget.Class);
	}

	// Sound //////
	static ConstructorHelpers::FObjectFinder<USoundCue> ChapterBGM(TEXT("SoundCue'/Game/Resource/Sound/ChapterBGM_Cue.ChapterBGM_Cue'"));
	if (ChapterBGM.Succeeded())
	{
		m_soundCueBGM = ChapterBGM.Object;
	}
	m_audioComponentBGM->SetSound(m_soundCueBGM);

	static ConstructorHelpers::FObjectFinder<USoundCue> BossBGM(TEXT("SoundCue'/Game/Resource/Sound/BossBGM_Cue.BossBGM_Cue'"));
	if (BossBGM.Succeeded())
	{
		m_bossCueBGM = BossBGM.Object;
	}

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
	m_audioComponentBGM->Play();

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

	if(m_curMapNumber != -1) m_bigmapManager->CheckVisitedBlocks(mapNumber, xPos, yPos);
}

int32 AChapterGameMode::GetCurMapNumber() const
{
	return m_curMapNumber;
}

void AChapterGameMode::VisibleBigmap(bool bVisibility)
{
	if (m_chapterResult) return;

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
	if (m_chapterResult) return;

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

void AChapterGameMode::AddEnemyCount(int32 mapNumber)
{
	if (m_enemyCount.Contains(mapNumber))
	{
		m_enemyCount[mapNumber]++;
	}
	else
	{
		m_enemyCount.Add(mapNumber);
		m_enemyCount[mapNumber] = 1;
	}
}

void AChapterGameMode::RemoveEnemy(int32 mapNumber)
{
	if (!m_enemyCount.Contains(mapNumber)) return;

	m_enemyCount[mapNumber]--;

	if (m_enemyCount[mapNumber] <= 0)
	{
		m_portalSystem->StartActivePortals(mapNumber);
	}
}

void AChapterGameMode::StartBossStage()
{
	StopBGM();

	m_audioComponentBGM->SetSound(m_bossCueBGM);
	m_audioComponentBGM->Play();
}

void AChapterGameMode::SetChapterResult(bool IsSuccess)
{
	m_chapterResult = true;
	m_mainWidget->RemoveFromViewport();
	m_bigmapWidget->RemoveFromViewport();
	m_inventoryWidget->RemoveFromViewport();

	StopBGM();

	if (IsSuccess)
	{
		m_successWidget->AddToViewport();
	}
	else
	{
		m_failWidget->AddToViewport();
	}
}