#pragma once

#include "CoreMinimal.h"
#include "Roguelike3DGameMode.h"
#include "IntroGameMode.generated.h"

UCLASS()
class ROGUELIKE3D_API AIntroGameMode : public ARoguelike3DGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay();

public:
	AIntroGameMode();
};
