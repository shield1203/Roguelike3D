#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EquipmentItem.h"
#include "CharacterAnimInstance.generated.h"

DECLARE_DELEGATE(FOnFireDelegate);

UCLASS()
class ROGUELIKE3D_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UAnimMontage* m_attackMontage;

	UPROPERTY()
	class ARoguelike3DCharacter* m_character;

	UPROPERTY()
	AEquipmentItem* m_characterWeapon;

	UPROPERTY()
	float m_attackPower;
public:
	FOnFireDelegate OnFire;

public:
	UCharacterAnimInstance();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_Fire();
};
