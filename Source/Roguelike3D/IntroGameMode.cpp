#include "IntroGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AIntroGameMode::AIntroGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> IntroWidget(TEXT("/Game/Widgets/Intro/WB_Intro"));
	if (IntroWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), IntroWidget.Class);
	}
}

void AIntroGameMode::StartPlay()
{
	Super::StartPlay();

	m_mainWidget->AddToViewport();
}