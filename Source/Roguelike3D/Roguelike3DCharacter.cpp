#include "Roguelike3DCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterAnimInstance.h"
#include "Inventory.h"
#include "EquipmentItem.h"
#include "PlayerProjectile.h"
#include "SkillProjetile.h"
#include "TimerManager.h"
#include "ChapterGameMode.h"

ARoguelike3DCharacter::ARoguelike3DCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_state = EPlayerState::Idle;

	m_inventory = CreateDefaultSubobject<UInventory>(TEXT("CharacterInventory"));

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f; 
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

	int32 MaterialIndex[7] = { 0, 1, 2, 3, 4 };
	for (auto Index : MaterialIndex)
	{
		GetMesh()->CreateDynamicMaterialInstance(Index);
	}

	//////
	m_ability.fMaxHP = 200.f;
	m_ability.fHP = 200.f;
	m_ability.fAttackPower = 10.f;
	m_ability.fDefensivPower = 0.f;
}

void ARoguelike3DCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARoguelike3DCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARoguelike3DCharacter::MoveRight);
}

void ARoguelike3DCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_characterAnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	m_characterAnimInstance->OnFire.BindUFunction(this, FName("Fire"));
	m_characterAnimInstance->OnTeleport.BindUFunction(this, FName("Teleport"));
	m_characterAnimInstance->OnTripleFire.BindUFunction(this, FName("TripleFire"));
	m_characterAnimInstance->OnDeath.BindUFunction(this, FName("Death"));
}

void ARoguelike3DCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ARoguelike3DCharacter::GetPlayerAttackPower()
{
	return m_ability.fAttackPower + m_inventory->GetWeaponValue();
}


int32 ARoguelike3DCharacter::GetPlayerDefensivePower()
{
	return m_ability.fDefensivPower + m_inventory->GetArmorValue();
}

int32 ARoguelike3DCharacter::GetPlayerCurHP()
{
	if (m_ability.fHP > GetPlayerMaxHP()) m_ability.fHP = m_ability.fMaxHP;
	return m_ability.fHP;
}

int32 ARoguelike3DCharacter::GetPlayerMaxHP()
{
	return m_ability.fMaxHP + m_inventory->GetAaccessoryValue();
}

float ARoguelike3DCharacter::GetPlayerPercentHP()
{
	float fCurHP = GetPlayerCurHP();
	float fMaxHP = GetPlayerMaxHP();

	return fCurHP / fMaxHP;
}

void ARoguelike3DCharacter::TakeDamagePlayer(float Damage)
{
	if (m_state == EPlayerState::Death) return;

	m_ability.fHP -= Damage;
	if (m_ability.fHP <= 0)
	{
		m_ability.fHP = 0;
		StartDeath();
	}

	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Damage"), 0.2f);
	GetWorldTimerManager().SetTimer(m_damageTimerHandle, this, &ARoguelike3DCharacter::DamageTimerFinished, 0.1f, false);
}

void ARoguelike3DCharacter::DamageTimerFinished()
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Damage"), 0.0f);
}

void ARoguelike3DCharacter::RecoveryHP(float value)
{
	m_ability.fHP += value;
	if (m_ability.fHP > m_ability.fMaxHP) m_ability.fHP = m_ability.fMaxHP;
}

void ARoguelike3DCharacter::MoveForward(float Value)
{
	if (m_state != EPlayerState::Idle) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value + m_ability.fSpeed);
	}
}

void ARoguelike3DCharacter::MoveRight(float Value)
{
	if (m_state != EPlayerState::Idle) return;

	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
		AddMovementInput(Direction, Value + m_ability.fSpeed);
	}
}

void ARoguelike3DCharacter::StartFire()
{
	m_characterAnimInstance->StartFire();
}

void ARoguelike3DCharacter::Fire()
{
	AEquipmentItem* pWeapon = Cast<AEquipmentItem>(m_inventory->GetWeapon());
	if (!pWeapon) return;

	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		APlayerProjectile* pProjectile = pWorld->SpawnActor<APlayerProjectile>(m_inventory->GetWeapon()->GetActorLocation(), GetActorRotation(), SpawnParams);
		if (pProjectile)
		{
			pProjectile->InitializePlayerProjectile(GetActorRotation().Vector(), pWeapon->GetItemCode(), GetPlayerAttackPower());
		}
	}
}

void ARoguelike3DCharacter::StartTeleport(FVector TeleportLocation)
{
	m_teleportLocation = TeleportLocation;
	m_teleportLocation.Z = GetActorLocation().Z;

	m_state = EPlayerState::Skill;
	m_characterAnimInstance->StartTeleport();
}

void ARoguelike3DCharacter::Teleport()
{
	SetActorLocation(m_teleportLocation, true);
	m_state = EPlayerState::Idle;
}

void ARoguelike3DCharacter::StartTripleFire()
{
	m_state = EPlayerState::Skill;
	m_characterAnimInstance->StartTripleFire();
}

void ARoguelike3DCharacter::TripleFire()
{
	m_state = EPlayerState::Idle;

	AEquipmentItem* pWeapon = Cast<AEquipmentItem>(m_inventory->GetWeapon());
	if (!pWeapon) return;

	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		for (int count = -1; count < 2; count++)
		{
			ASkillProjetile* pProjectile = pWorld->SpawnActor<ASkillProjetile>(m_inventory->GetWeapon()->GetActorLocation(), GetActorRotation(), SpawnParams);
			if (pProjectile)
			{
				FRotator projectileRotation = GetActorRotation();
				projectileRotation.Yaw += (count * 30);
				pProjectile->InitializeProjectile(projectileRotation.Vector(), GetPlayerAttackPower());
			}
		}
	}
}

void ARoguelike3DCharacter::StartDeath()
{
	m_state = EPlayerState::Death;
	m_characterAnimInstance->StartDeath();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, -100);
}

void ARoguelike3DCharacter::Death()
{
	AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (pGameMode)
	{
		pGameMode->SetChapterResult(false);
	}
}