#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Enemy_Grim.generated.h"

UCLASS(BlueprintType)
class ROGUELIKE3D_API AEnemy_Grim : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	class UAIPerceptionStimuliSourceComponent* m_stimulusComponent;

	class UGrimAnimInstance* m_grimAnimInstance;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	AEnemy_Grim();

	virtual void TakeDamageEnemy(float Damage) override;

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void Death();
};
