#include "TitleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "TitleController.h"

ATitleGameMode::ATitleGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidget(TEXT("/Game/Widgets/Title/WB_Title"));
	if (TitleWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), TitleWidget.Class);
	}

	PlayerControllerClass = ATitleController::StaticClass();
}

void ATitleGameMode::StartPlay()
{
	Super::StartPlay();

	m_mainWidget->AddToViewport();
}