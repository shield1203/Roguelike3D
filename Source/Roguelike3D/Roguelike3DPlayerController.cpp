#include "Roguelike3DPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "EnemyBase.h"
#include "ChapterGameMode.h"

ARoguelike3DPlayerController::ARoguelike3DPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARoguelike3DPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	SetPlayerRotation();
}

void ARoguelike3DPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("StartFire", IE_Pressed, this, &ARoguelike3DPlayerController::OnFire);
	InputComponent->BindAction("Teleport", IE_Pressed, this, &ARoguelike3DPlayerController::OnTeleport);
	InputComponent->BindAction("TripleFire", IE_Pressed, this, &ARoguelike3DPlayerController::OnTripleFire);

	InputComponent->BindAction("BigMap", IE_Pressed, this, &ARoguelike3DPlayerController::OnOpenBigmap);
	InputComponent->BindAction("BigMap", IE_Released, this, &ARoguelike3DPlayerController::OnCloseBigmap);

	InputComponent->BindAction("InventoryUI", IE_Pressed, this, &ARoguelike3DPlayerController::OnFlipInventory);
}

void ARoguelike3DPlayerController::SetPlayerRotation()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		FVector Point = Hit.ImpactPoint;

		AEnemyBase* pEnemy = Cast<AEnemyBase>(Hit.GetActor());
		if (pEnemy)
		{
			Point = pEnemy->GetActorLocation();
		}

		ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(GetPawn());
		if (pPlayerPawn && !pPlayerPawn->IsSkilling())
		{
			float fRadian = FMath::Atan2(Point.Y - pPlayerPawn->GetActorLocation().Y, Point.X - pPlayerPawn->GetActorLocation().X);
			float fDegree = FMath::RadiansToDegrees(fRadian);

			pPlayerPawn->SetActorRotation(FRotator(0, fDegree, 0));
		}
	}
}

void ARoguelike3DPlayerController::OnFire()
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(GetPawn());
	if (pPlayerPawn && !pPlayerPawn->IsSkilling())
	{
		pPlayerPawn->StartFire();
	}
}

void ARoguelike3DPlayerController::OnTeleport()
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(GetPawn());
	if (pPlayerPawn && !pPlayerPawn->IsSkilling())
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			pPlayerPawn->StartTeleport(Hit.ImpactPoint);
		}
	}
}

void ARoguelike3DPlayerController::OnTripleFire()
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(GetPawn());
	if (pPlayerPawn && !pPlayerPawn->IsSkilling())
	{
		pPlayerPawn->StartTripleFire();
	}
}

void ARoguelike3DPlayerController::OnOpenBigmap()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			pGameMode->VisibleBigmap(true);
		}
	}
}

void ARoguelike3DPlayerController::OnCloseBigmap()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			pGameMode->VisibleBigmap(false);
		}
	}
}

void ARoguelike3DPlayerController::OnFlipInventory()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			pGameMode->FlipInventory();
		}
	}
}