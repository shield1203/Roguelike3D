#include "Roguelike3DGameMode.h"
#include "Roguelike3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARoguelike3DGameMode::ARoguelike3DGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
