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

	// ��ƼŬ

	// Ÿ�̸��ڵ鷯
	
	// ����ð�

	// �ִ�ð�

	UPROPERTY()
	float m_maxValue;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	ABossSkillObject();

	//void �ð� ������ ���׸��� ����, ��������

	//void �ִ�ð���� �÷��̾� ����, ��ƼŬ ����, �����
};
