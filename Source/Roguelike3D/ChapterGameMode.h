#pragma once

#include "CoreMinimal.h"
#include "Roguelike3DGameMode.h"
#include "ChapterGameMode.generated.h"

UCLASS()
class ROGUELIKE3D_API AChapterGameMode : public ARoguelike3DGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay();

public:
	AChapterGameMode();

};
