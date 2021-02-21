#include "BossAnimInstance.h"

UBossAnimInstance::UBossAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> PatternAMontage(TEXT("AnimMontage'/Game/Animations/Boss/PatternA_Montage.PatternA_Montage'"));
	if (PatternAMontage.Succeeded())
	{
		m_patternAMontage = PatternAMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> PatternBMontage(TEXT("AnimMontage'/Game/Animations/Boss/PatternB_Montage.PatternB_Montage'"));
	if (PatternBMontage.Succeeded())
	{
		m_patternBMontage = PatternBMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> PatternCMontage(TEXT("AnimMontage'/Game/Animations/Boss/PatternC_Montage.PatternC_Montage'"));
	if (PatternCMontage.Succeeded())
	{
		m_patternCMontage = PatternCMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontage(TEXT("AnimMontage'/Game/Animations/Boss/Death_Montage.Death_Montage'"));
	if (DeathMontage.Succeeded())
	{
		m_deathMontage = DeathMontage.Object;
	}
}

void UBossAnimInstance::AnimNotify_End()
{
	OnEnd.ExecuteIfBound();
}

void UBossAnimInstance::StartPatternA()
{
	Montage_Play(m_patternAMontage, 1.0f);
}

void UBossAnimInstance::AnimNotify_PatternA()
{
	OnPattrenA.ExecuteIfBound();
}

void UBossAnimInstance::StartPatternB()
{
	Montage_Play(m_patternBMontage, 1.0f);
}

void UBossAnimInstance::AnimNotify_PatternB()
{
	OnPattrenB.ExecuteIfBound();
}

void UBossAnimInstance::StartPatternC()
{
	Montage_Play(m_patternCMontage, 1.0f);
}

void UBossAnimInstance::AnimNotify_PatternC()
{
	OnPattrenC.ExecuteIfBound();
}

void UBossAnimInstance::StartDeath()
{
	Montage_Play(m_deathMontage, 1.0f);
}

void UBossAnimInstance::AnimNotify_Death()
{
	OnDeath.ExecuteIfBound();
}