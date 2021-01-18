#pragma once

#include "CoreMinimal.h"
#include "Roguelike3DGameMode.h"
#include "ChapterGameMode.generated.h"

class UPortalSystem;

UCLASS()
class ROGUELIKE3D_API AChapterGameMode : public ARoguelike3DGameMode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "GameMode_System")
	UPortalSystem* m_portalSystem;

protected:
	virtual void StartPlay();

public:
	AChapterGameMode();

	class APortal* GetArrivalPortal(int32 mapNumber, int32 portalNumber);
};
