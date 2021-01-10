#pragma once

#include "CoreMinimal.h"
#include "Roguelike3DGameMode.h"
#include "TitleGameMode.generated.h"

UCLASS()
class ROGUELIKE3D_API ATitleGameMode : public ARoguelike3DGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay();

public:
	ATitleGameMode();
};
