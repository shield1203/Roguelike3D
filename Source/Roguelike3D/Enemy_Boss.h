#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Enemy_Boss.generated.h"

UCLASS()
class ROGUELIKE3D_API AEnemy_Boss : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class UBossAnimInstance* m_bossAnimInstance;

	UPROPERTY(VisibleAnywhere)
	int32 m_maxPattern;

	UPROPERTY(VisibleAnywhere)
	int32 m_curPattern;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaTime) override;

public:
	AEnemy_Boss();

	void StartPattern();

	void Pattern0();

	void Pattern1();

	void Pattern2();

	void EndPattern();
};
