#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GrimAnimInstance.generated.h"

DECLARE_DELEGATE(FOnFireDelegate);
DECLARE_DELEGATE(FOnDeathDelegate);

UCLASS()
class ROGUELIKE3D_API UGrimAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UAnimMontage* m_attackMontage;

	UPROPERTY()
	UAnimMontage* m_deathMontage;

public:
	FOnFireDelegate OnFire;

	FOnDeathDelegate OnDeath;

public:
	UGrimAnimInstance();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Fire();

	UFUNCTION(BlueprintCallable)
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Death();
};