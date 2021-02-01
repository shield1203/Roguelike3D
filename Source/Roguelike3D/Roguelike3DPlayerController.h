#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Roguelike3DPlayerController.generated.h"

UCLASS()
class ROGUELIKE3D_API ARoguelike3DPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	void SetPlayerRotation();

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

public:
	ARoguelike3DPlayerController();

	void OnOpenBigmap();

	void OnCloseBigmap();

	void OnFlipInventory();
};
