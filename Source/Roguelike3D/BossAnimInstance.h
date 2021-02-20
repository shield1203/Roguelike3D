#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

DECLARE_DELEGATE(FOnPattern0Delegate);
DECLARE_DELEGATE(FOnPattern1Delegate);
DECLARE_DELEGATE(FOnPattern2Delegate);
DECLARE_DELEGATE(FOnDeathDelegate);

UCLASS()
class ROGUELIKE3D_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UAnimMontage* m_startMontage;
	
	

	UPROPERTY()
	UAnimMontage* m_deathMontage;

public:
	FOnPattern0Delegate OnPattren0;

	FOnPattern0Delegate OnPattren1;

	FOnPattern0Delegate OnPattren2;

	FOnDeathDelegate OnDeath;

public:
	UBossAnimInstance();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_End();

	UFUNCTION(BlueprintCallable)
	void StartPattern0();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Pattern0();

	UFUNCTION(BlueprintCallable)
	void StartPattern1();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Pattern1();

	UFUNCTION(BlueprintCallable)
	void StartPattern2();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Pattern2();

	UFUNCTION(BlueprintCallable)
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Death();
};
