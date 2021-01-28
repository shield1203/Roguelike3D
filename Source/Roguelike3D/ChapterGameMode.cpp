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

	m_portalSystem = CreateDefaultSubobject<UPortalSystem>(TEXT("GameMode_PortalSystem"));
	m_chapterAssetManager = CreateDefaultSubobject<UChapterAssetManager>(TEXT("GameMode_ChapterAssetManager"));
	m_bigmapManager = CreateDefaultSubobject<UBigmapManager>(TEXT("GameMode_BigmapManager"));
	m_minimapManager = CreateDefaultSubobject<UMinimapManager>(TEXT("GameMode_MinimapManager"));
}

void AChapterGameMode::StartPlay()
{
	Super::StartPlay();

	m_portalSystem->SetRandomRoguelikeMap();

	m_mainWidget->AddToViewport();
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
