#include "GrimAnimInstance.h"
#include "UObject/ConstructorHelpers.h"

UGrimAnimInstance::UGrimAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontage(TEXT("AnimMontage'/Game/Animations/Grim/Fire_Montage.Fire_Montage'"));
	if (AttackMontage.Succeeded())
	{
		m_attackMontage = AttackMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontage(TEXT("AnimMontage'/Game/Animations/Grim/Death_Montage.Death_Montage'"));
	if (DeathMontage.Succeeded())
	{
		m_deathMontage = DeathMontage.Object;
	}
}

void UGrimAnimInstance::StartFire()
{
	Montage_Play(m_attackMontage, 1.0f);
}

void UGrimAnimInstance::AnimNotify_Fire()
{
	OnFire.ExecuteIfBound();
}

void UGrimAnimInstance::StartDeath()
{
	Montage_Play(m_deathMontage, 1.0f);
}

void UGrimAnimInstance::AnimNotify_Death()
{
	OnDeath.ExecuteIfBound();
}