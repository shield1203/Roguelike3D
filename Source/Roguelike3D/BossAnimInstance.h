#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

DECLARE_DELEGATE(FOnPatternADelegate);
DECLARE_DELEGATE(FOnPatternBDelegate);
DECLARE_DELEGATE(FOnPatternCDelegate);
DECLARE_DELEGATE(FOnDeathDelegate);
DECLARE_DELEGATE(FOnEndDelegate);

UCLASS()
class ROGUELIKE3D_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UAnimMontage* m_patternAMontage;
	
	UPROPERTY()
	UAnimMontage* m_patternBMontage;

	UPROPERTY()
	UAnimMontage* m_patternCMontage;

	UPROPERTY()
	UAnimMontage* m_deathMontage;

public:
	FOnPatternADelegate OnPattrenA;

	FOnPatternBDelegate OnPattrenB;

	FOnPatternCDelegate OnPattrenC;

	FOnDeathDelegate OnDeath;

	FOnEndDelegate OnEnd;

public:
	UBossAnimInstance();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_End();

	UFUNCTION(BlueprintCallable)
	void StartPatternA();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_PatternA();

	UFUNCTION(BlueprintCallable)
	void StartPatternB();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_PatternB();

	UFUNCTION(BlueprintCallable)
	void StartPatternC();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_PatternC();

	UFUNCTION(BlueprintCallable)
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Death();
};
