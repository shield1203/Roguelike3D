#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSkillObject.generated.h"

UCLASS()
class ROGUELIKE3D_API ABossSkillObject : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* m_collisionComponent;

	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* m_decalComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystem* m_particleSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* m_rangeMaterial;

	UPROPERTY()
	float m_leftTime;

	UPROPERTY()
	float m_maxTime;

	UPROPERTY()
	float m_maxValue;

	UPROPERTY()
	float m_damage;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void ProgressRange(float fProgressPercent);

	void FinishedTimer();

public:	
	ABossSkillObject();

	void InitializeSkillObject(float fDamage, float fMaxTime);
};
