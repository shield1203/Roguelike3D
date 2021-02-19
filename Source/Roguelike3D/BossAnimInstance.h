#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

DECLARE_DELEGATE(FOnDeathDelegate);

UCLASS()
class ROGUELIKE3D_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

public:
	FOnDeathDelegate OnDeath;

public:
	UBossAnimInstance();
};
