#include "TitleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "TitleController.h"

ATitleGameMode::ATitleGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidget(TEXT("/Game/Widgets/Title/WB_Title"));
	if (TitleWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), TitleWidget.Class);
	}

	PlayerControllerClass = ATitleController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USoundCue> TitleBGM(TEXT("SoundCue'/Game/Resource/Sound/TitleBGM_Cue.TitleBGM_Cue'"));
	if (TitleBGM.Succeeded())
	{
		m_soundCueBGM = TitleBGM.Object;
	}
	m_audioComponentBGM->SetSound(m_soundCueBGM);
}

void ATitleGameMode::StartPlay()
{
	Super::StartPlay();

	m_mainWidget->AddToViewport();
	m_audioComponentBGM->Play();
}