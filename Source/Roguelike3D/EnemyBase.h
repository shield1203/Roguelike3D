#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyCode : uint8
{
	Grim UMETA(DisplayName = "Grim"),
	SpellTower_Fire UMETA(DisplayName = "SpellTower_Fire"),
	SpellTower_Ice UMETA(DisplayName = "SpellTower_Ice"),
};

UCLASS()
class ROGUELIKE3D_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()	

protected:
	EEnemyCode m_enemyCode;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	AEnemyBase();

};
