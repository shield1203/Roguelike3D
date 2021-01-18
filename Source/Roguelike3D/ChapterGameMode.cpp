#include "ChapterGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Roguelike3DPlayerController.h"
#include "Roguelike3DCharacter.h"
#include "PortalSystem.h"
#include "Portal.h"

AChapterGameMode::AChapterGameMode()
{	
	PlayerControllerClass = ARoguelike3DPlayerController::StaticClass();

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
}

void AChapterGameMode::StartPlay()
{
	Super::StartPlay();

	m_mainWidget->AddToViewport();

	m_portalSystem->SetRandomRoguelikeMap();
}

APortal* AChapterGameMode::GetArrivalPortal(int32 mapNumber, int32 portalNumber)
{
	return m_portalSystem->GetArrivalPortal(mapNumber, portalNumber);
}