#include "MinimapManager.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "Roguelike3DCharacter.h"
#include "Portal.h"

UMinimapManager::UMinimapManager()
{
	UDataTable* pMinimapDataTable = LoadObject<UDataTable>(this, TEXT("/Game/DataTable/Minimap"));

	for (int mapNumber = 0; mapNumber < pMinimapDataTable->GetRowNames().Num(); mapNumber++)
	{
		FMinimapData* pMinimapData = pMinimapDataTable->FindRow<FMinimapData>(FName(*(FString::FormatAsNumber(mapNumber))), FString(""));
		m_MinimapData.Add(mapNumber);
		m_MinimapData[mapNumber].XPos = pMinimapData->XPos;
		m_MinimapData[mapNumber].YPos = pMinimapData->YPos;
		m_MinimapData[mapNumber].Width = pMinimapData->Width;
		m_MinimapData[mapNumber].Height = pMinimapData->Height;
		m_MinimapData[mapNumber].MinimapTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pMinimapData->MinimapPath)));
	}
}

FVector2D UMinimapManager::GetPlayerIconLocation(int32 mapNumber)
{
	FVector2D PlayerIconLocation;

	ARoguelike3DCharacter* pPlayer = Cast<ARoguelike3DCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (pPlayer != nullptr)
	{
		float fMoveDistance = pPlayer->GetActorLocation().Y - m_MinimapData[mapNumber].YPos;
		PlayerIconLocation.X = (fMoveDistance / m_MinimapData[mapNumber].Height) * GetMinimapTextureSize(mapNumber).X;

		fMoveDistance = pPlayer->GetActorLocation().X - m_MinimapData[mapNumber].XPos;
		PlayerIconLocation.Y = (1 - (fMoveDistance / m_MinimapData[mapNumber].Width)) * GetMinimapTextureSize(mapNumber).Y;
	}

	return PlayerIconLocation;
}

FVector2D UMinimapManager::GetPortalIconLocation(int32 mapNumber, int32 portalNumber)
{
	FVector2D PortalconLocation = FVector2D(-1.f);

	UWorld* world = GetWorld();
	for (TActorIterator<APortal> portal(world); portal; ++portal)
	{
		if (portal->GetMapNumber() == mapNumber && portal->GetPortalNumber() == portalNumber)
		{
			APortal* pPortalActor = Cast<APortal>(*portal);

			float fActorLocation = pPortalActor->GetActorLocation().Y - m_MinimapData[mapNumber].YPos;
			PortalconLocation.X = (fActorLocation / m_MinimapData[mapNumber].Height) * GetMinimapTextureSize(mapNumber).X;

			fActorLocation = pPortalActor->GetActorLocation().X - m_MinimapData[mapNumber].XPos;
			PortalconLocation.Y = (1 - (fActorLocation / m_MinimapData[mapNumber].Width)) * GetMinimapTextureSize(mapNumber).Y;
			break;
		}
	}

	return PortalconLocation;
}

FVector2D UMinimapManager::GetMinimapTextureSize(int32 mapNumber)
{
	FVector2D TextureSize;
	TextureSize.X = m_MinimapData[mapNumber].MinimapTexture->GetSizeX() * 0.375;
	TextureSize.Y = m_MinimapData[mapNumber].MinimapTexture->GetSizeY() * 0.375;

	return TextureSize;
}

UTexture2D* UMinimapManager::GetMinimaptexture(int32 mapNumber) const
{
	return m_MinimapData[mapNumber].MinimapTexture;
}