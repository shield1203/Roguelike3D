#include "ChapterGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Roguelike3DPlayerController.h"
#include "Roguelike3DCharacter.h"
#include "PortalSystem.h"
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

	m_portalSystem = CreateDefaultSubobject<UPortalSystem>(TEXT("GameMode_PortalSystem"));
	m_minimapManager = CreateDefaultSubobject<UMinimapManager>(TEXT("GameMode_MinimapManager"));
}

void AChapterGameMode::StartPlay()
{
	Super::StartPlay();

	m_portalSystem->SetRandomRoguelikeMap();

	m_mainWidget->AddToViewport();
}

UMinimapManager* AChapterGameMode::GetMinimapManager() const
{
	return m_minimapManager;
}

void AChapterGameMode::SetCurMapNumber(int32 mapNumber)
{
	m_curMapNumber = mapNumber;
}

int32 AChapterGameMode::GetCurMapNumber() const
{
	return m_curMapNumber;
}