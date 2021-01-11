#include "ChapterGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Roguelike3DPlayerController.h"
#include "Roguelike3DCharacter.h"

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
}

void AChapterGameMode::StartPlay()
{
	Super::StartPlay();

	m_mainWidget->AddToViewport();
}