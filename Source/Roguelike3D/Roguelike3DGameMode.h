#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Roguelike3DGameMode.generated.h"

UCLASS(minimalapi)
class ARoguelike3DGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnyWhere, Category = "GameMode_Widget", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* m_mainWidget;
};