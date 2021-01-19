#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Roguelike3DCharacter.generated.h"

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fDefensivPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAttackSpeed;
};

UCLASS(config=Game)
class ARoguelike3DCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	FAbilityData m_ability;

public:
	ARoguelike3DCharacter();

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

