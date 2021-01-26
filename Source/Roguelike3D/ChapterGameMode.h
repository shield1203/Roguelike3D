#pragma once

#include "CoreMinimal.h"
#include "Roguelike3DGameMode.h"
#include "ChapterGameMode.generated.h"

class UPortalSystem;
class UBigmapManager;
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

	UPROPERTY(EditAnywhere, Category = "GameMode_Manager")
	UBigmapManager* m_bigmapManager;

	UPROPERTY(EditAnyWhere, Category = "GameMode_Widget", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* m_bigmapWidget;

	UPROPERTY()
	int32 m_curMapNumber;

protected:
	virtual void StartPlay();

public:
	AChapterGameMode();

	UFUNCTION(Blueprintcallable)
	UBigmapManager* GetBigmapManager() const;

	UFUNCTION(Blueprintcallable)
	UMinimapManager* GetMinimapManager() const;

	void SetCurMapNumber(int32 mapNumber, int32 xPos, int32 yPos);

	UFUNCTION(Blueprintcallable)
	int32 GetCurMapNumber() const;

	void VisibleBigmap(bool bVisibility);
};