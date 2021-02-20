#include "BossAnimInstance.h"

UBossAnimInstance::UBossAnimInstance()
{

}

void UBossAnimInstance::AnimNotify_End()
{

}

void UBossAnimInstance::StartPattern0()
{

}

void UBossAnimInstance::AnimNotify_Pattern0()
{

}

void UBossAnimInstance::StartPattern1()
{

}

void UBossAnimInstance::AnimNotify_Pattern1()
{

}

void UBossAnimInstance::StartPattern2()
{

}

void UBossAnimInstance::AnimNotify_Pattern2()
{

}

void UBossAnimInstance::StartDeath()
{

}

void UBossAnimInstance::AnimNotify_Death()
{
	OnDeath.ExecuteIfBound();
}