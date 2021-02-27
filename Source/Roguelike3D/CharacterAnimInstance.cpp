#include "CharacterAnimInstance.h"
#include "UObject/ConstructorHelpers.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage>AttackMontage(TEXT("AnimMontage'/Game/Animations/Player/Fire_Montage.Fire_Montage'"));
	if (AttackMontage.Succeeded())
	{
		m_attackMontage = AttackMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage>TeleportMontage(TEXT("AnimMontage'/Game/Animations/Player/Teleport_Montage.Teleport_Montage'"));
	if (TeleportMontage.Succeeded())
	{
		m_teleportMontage = TeleportMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage>TripleFireMontage(TEXT("AnimMontage'/Game/Animations/Player/TripleFire_Montage.TripleFire_Montage'"));
	if (TripleFireMontage.Succeeded())
	{
		m_tripleFireMontage = TripleFireMontage.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage>DeathMontage(TEXT("AnimMontage'/Game/Animations/Player/Death_Montage.Death_Montage'"));
	if (DeathMontage.Succeeded())
	{
		m_deathMontage = DeathMontage.Object;
	}
}

void UCharacterAnimInstance::StartFire()
{
	Montage_Play(m_attackMontage, 1.0f);
}

void UCharacterAnimInstance::AnimNotify_Fire()
{
	OnFire.ExecuteIfBound();
}

void UCharacterAnimInstance::StartTeleport()
{
	Montage_Play(m_teleportMontage, 1.0f);
}

void UCharacterAnimInstance::AnimNotify_Teleport()
{
	OnTeleport.ExecuteIfBound();
}

void UCharacterAnimInstance::StartTripleFire()
{
	Montage_Play(m_tripleFireMontage, 1.0f);
}

void UCharacterAnimInstance::AnimNotify_TripleFire()
{
	OnTripleFire.ExecuteIfBound();
}

void UCharacterAnimInstance::StartDeath()
{
	Montage_Play(m_deathMontage, 1.0f);
}

void UCharacterAnimInstance::AnimNotify_Death()
{
	OnDeath.ExecuteIfBound();
}