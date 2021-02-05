#include "CharacterAnimInstance.h"
#include "UObject/ConstructorHelpers.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontage(TEXT("AnimMontage'/Game/Animations/Player/Fire_Montage.Fire_Montage'"));
	if (AttackMontage.Succeeded())
	{
		m_attackMontage = AttackMontage.Object;
	}
}

void UCharacterAnimInstance::StartFire()
{
	Montage_Play(m_attackMontage, 1.0f);
}

void UCharacterAnimInstance::AnimNotify_Fire()
{
	OnFire.Execute();
}