#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EquipmentItem.h"
#include "CharacterAnimInstance.generated.h"

DECLARE_DELEGATE(FOnFireDelegate);
DECLARE_DELEGATE(FOnTeleportDelegate);
DECLARE_DELEGATE(FOnTripleFireDelegate);
DECLARE_DELEGATE(FOnDeathDelegate);

UCLASS()
class ROGUELIKE3D_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UAnimMontage* m_attackMontage;

	UPROPERTY()
	UAnimMontage* m_teleportMontage;

	UPROPERTY()
	UAnimMontage* m_tripleFireMontage;

	UPROPERTY()
	UAnimMontage* m_deathMontage;

public:
	FOnFireDelegate OnFire;

	FOnTeleportDelegate OnTeleport;

	FOnTripleFireDelegate OnTripleFire;

	FOnDeathDelegate OnDeath;

public:
	UCharacterAnimInstance();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Fire();

	UFUNCTION(BlueprintCallable)
	void StartTeleport();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Teleport();

	UFUNCTION(BlueprintCallable)
	void StartTripleFire();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_TripleFire();

	UFUNCTION(BlueprintCallable)
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Death();
};
