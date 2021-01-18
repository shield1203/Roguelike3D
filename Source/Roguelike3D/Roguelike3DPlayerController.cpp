#include "Roguelike3DPlayerController.h"
#include "Roguelike3DCharacter.h"

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

	//InputComponent->BindAction("PrintAngle", IE_Pressed, this, &ARoguelike3DPlayerController::OnPrintAnglePressed);
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