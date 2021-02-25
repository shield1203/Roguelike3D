#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyCode : uint8
{
	Grim_White UMETA(DisplayName = "Grim_White"),
	Grim_Red UMETA(DisplayName = "Grim_Red"),
	Grim_Green UMETA(DisplayName = "Grim_Green"),
	Boss UMETA(DisplayName = "Boss"),
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Attack UMETA(DisplayName = "Attack"),
	Damage UMETA(DisplayName = "Damage"),
	Death UMETA(DisplayName = "Death"),
};

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyCode EnemyCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefensivPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;
};

UCLASS()
class ROGUELIKE3D_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EEnemyCode m_enemyCode;

	UPROPERTY(VisibleAnywhere)
	FEnemyData m_enemyData;

	UPROPERTY(VisibleAnywhere)
	float m_curHP;

	UPROPERTY(VisibleAnywhere)
	EEnemyState m_enemyState;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystem* m_particleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* m_HPBarWidget;

	FTimerHandle m_damageTimerHandle;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void LoadEnemyData();

public:	
	AEnemyBase();

	virtual void TakeDamageEnemy(float Damage);

	void DamageTimerFinished();

	void SetEnemyState(EEnemyState state);

	EEnemyState GetEnemyState() const;

	float GetAttackRange() const;

	UFUNCTION(BlueprintCallable)
	float CurHPPercent() const;
};
