#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EquipmentItem.h"
#include "CharacterAnimInstance.generated.h"

DECLARE_DELEGATE(FOnFireDelegate);
DECLARE_DELEGATE(FOnTeleportDelegate);

UCLASS()
class ROGUELIKE3D_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UAnimMontage* m_attackMontage;

	UPROPERTY()
	UAnimMontage* m_teleportMontage;

public:
	FOnFireDelegate OnFire;

	FOnTeleportDelegate OnTeleport;

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
};
