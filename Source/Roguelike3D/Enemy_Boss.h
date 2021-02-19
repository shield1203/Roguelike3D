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
	bool m_skilling;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	AEnemy_Boss();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_SkillEnd();
};
