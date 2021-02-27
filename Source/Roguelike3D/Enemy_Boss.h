#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Enemy_Boss.generated.h"

UCLASS()
class ROGUELIKE3D_API AEnemy_Boss : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	class UBossAnimInstance* m_bossAnimInstance;

	UPROPERTY(VisibleAnywhere)
	int32 m_maxPattern;

	UPROPERTY(VisibleAnywhere)
	int32 m_curPattern;

protected:
	UPROPERTY(EditAnyWhere, Category = "BossWidget", meta = (AllowPrivateAccess = "true"))
	class UWidgetBase* m_BossHPBarWidget;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaTime) override;

public:
	AEnemy_Boss();

	virtual void TakeDamageEnemy(float Damage) override;

	void StartPattern();

	UFUNCTION(BlueprintCallable)
	void PatternA();

	UFUNCTION(BlueprintCallable)
	void PatternB();

	UFUNCTION(BlueprintCallable)
	void PatternC();

	UFUNCTION(BlueprintCallable)
	void EndPattern();

	UFUNCTION(BlueprintCallable)
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void Death();
};
