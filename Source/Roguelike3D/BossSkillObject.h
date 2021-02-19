#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSkillObject.generated.h"

UCLASS()
class ROGUELIKE3D_API ABossSkillObject : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY()
	class UDecalComponent* m_decalComponent;

	// 파티클

	// 타이머핸들러
	
	// 경과시간

	// 최대시간

	UPROPERTY()
	float m_maxValue;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	ABossSkillObject();

	//void 시간 지나면 메테리얼값 변경, 범위변경

	//void 최대시간경과 플레이어 공격, 파티클 스폰, 사라짐
};
