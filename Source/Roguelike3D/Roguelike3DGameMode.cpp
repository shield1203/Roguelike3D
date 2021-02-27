#include "Roguelike3DGameMode.h"
#include "Components/AudioComponent.h"

ARoguelike3DGameMode::ARoguelike3DGameMode()
{
	m_audioComponentBGM = CreateDefaultSubobject<UAudioComponent>(TEXT("GameModeAudioComponent"));
	m_audioComponentBGM->bAutoActivate = false;
}

void ARoguelike3DGameMode::StopBGM()
{
	if (m_audioComponentBGM->IsPlaying())
	{
		m_audioComponentBGM->Stop();
	}
}