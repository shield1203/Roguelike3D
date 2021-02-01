#include "Roguelike3DPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
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
		ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(GetPawn());
		if (pPlayerPawn)
		{
			float fRadian = FMath::Atan2(Hit.ImpactPoint.Y - pPlayerPawn->GetActorLocation().Y, Hit.ImpactPoint.X - pPlayerPawn->GetActorLocation().X);
			float fDegree = FMath::RadiansToDegrees(fRadian);

			pPlayerPawn->SetActorRotation(FRotator(0, fDegree, 0));
		}
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