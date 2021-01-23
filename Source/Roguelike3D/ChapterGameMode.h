#pragma once

#include "CoreMinimal.h"
#include "Roguelike3DGameMode.h"
#include "ChapterGameMode.generated.h"

class UPortalSystem;
class UMinimapManager;

UCLASS()
class ROGUELIKE3D_API AChapterGameMode : public ARoguelike3DGameMode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "GameMode_System")
	UPortalSystem* m_portalSystem;

	UPROPERTY(EditAnywhere, Category = "GameMode_Manager")
	UMinimapManager* m_minimapManager;

	UPROPERTY()
	int32 m_curMapNumber;

protected:
	virtual void StartPlay();

public:
	AChapterGameMode();

	UFUNCTION(Blueprintcallable)
	class UMinimapManager* GetMinimapManager() const;

	void SetCurMapNumber(int32 mapNumber);

	UFUNCTION(Blueprintcallable)
	int32 GetCurMapNumber() const;

};
