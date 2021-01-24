#include "PortalSystem.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Portal.h"

UPortalSystem::UPortalSystem()
{
	m_maxMapNumber = 5;
	m_maxPortalCount = 4;
}

void UPortalSystem::InitializePortalData()
{
	m_remainMapNumber.Empty();

	m_portals.Empty();
	for (int mapNumber = 0; mapNumber < m_maxMapNumber; mapNumber++)
	{
		m_remainMapNumber.Add(mapNumber);

		m_portals.Add(mapNumber);
		m_portals[mapNumber].number.Init(-1, m_maxPortalCount);
	}
	m_remainMapNumber.Remove(0);

	m_mapPos.Empty();
	m_mapPos.Add(FMapPos());
}

void UPortalSystem::SetRandomRoguelikeMap()
{
	InitializePortalData();

	while (m_remainMapNumber.Num() > 0)
	{
		AttachMap();
	}

	SetArrivalPortals();
}

void UPortalSystem::AttachMap()
{
	srand((unsigned int)time(0));

	int32 randomMapIndex = rand() % m_mapPos.Num();
	int32 randomMapNumber = m_mapPos[randomMapIndex].mapNumber;

	int32 portalDirection = rand() % m_maxPortalCount;

	if (m_portals[randomMapNumber].number[portalDirection] == -1 && IsEmptyPos(m_mapPos[randomMapIndex].xPos, m_mapPos[randomMapIndex].yPos, portalDirection))
	{
		int32 mapNumberIndex = rand() % m_remainMapNumber.Num();
		int32 attachMapNumber = m_remainMapNumber[mapNumberIndex];

		m_portals[randomMapNumber].number[portalDirection] = attachMapNumber;

		int32 directionXPos = m_mapPos[randomMapIndex].xPos;
		int32 directionYPos = m_mapPos[randomMapIndex].yPos;

		switch (portalDirection)
		{
		case 0: m_portals[attachMapNumber].number[2] = randomMapNumber; directionYPos += 1; break; // North
		case 1: m_portals[attachMapNumber].number[3] = randomMapNumber; directionXPos += 1; break; // East
		case 2: m_portals[attachMapNumber].number[0] = randomMapNumber; directionYPos -= 1; break; // South
		case 3: m_portals[attachMapNumber].number[1] = randomMapNumber; directionXPos -= 1; break; // West
		}

		m_mapPos.Add(FMapPos(attachMapNumber, directionXPos, directionYPos));
		m_remainMapNumber.Remove(attachMapNumber);
	}
}

bool UPortalSystem::IsEmptyPos(int32 xPos, int32 yPos, int32 direction)
{
	switch (direction)
	{
	case 0: yPos += 1; break; // North
	case 1: xPos += 1; break; // East
	case 2: yPos -= 1; break; // South
	case 3: xPos -= 1; break; // West
	}

	for (auto mapPos : m_mapPos)
	{
		if (mapPos.xPos == xPos && mapPos.yPos == yPos)
		{
			return false;
		}
	}

	return true;
}

FIntPoint UPortalSystem::GetMapPos(int32 mapNumber)
{
	FIntPoint mapPos = FIntPoint(0);

	for (auto pos : m_mapPos)
	{
		if (pos.mapNumber == mapNumber)
		{
			mapPos.X = pos.xPos;
			mapPos.Y = pos.yPos;
		}
	}

	return mapPos;
}

void UPortalSystem::SetArrivalPortals()
{
	UWorld* world = GetWorld();

	for (TActorIterator<APortal> portal(world); portal; ++portal)
	{
		FIntPoint portalMapPos = GetMapPos(portal->GetMapNumber());
		portal->SetArrivalPortal(GetArrivalPortal(portal->GetMapNumber(), portal->GetPortalNumber()), portalMapPos.X, portalMapPos.Y);
	}
}

APortal* UPortalSystem::GetArrivalPortal(int32 mapNumber, int32 portalNumber)
{
	APortal* pArrivalPortal = nullptr;

	if(m_portals[mapNumber].number[portalNumber] == -1) return pArrivalPortal;

	UWorld* world = GetWorld();
	int32 arrivalPortalNumber;

	switch (portalNumber)
	{
	case 0: arrivalPortalNumber = 2; break; // North
	case 1: arrivalPortalNumber = 3; break; // East
	case 2: arrivalPortalNumber = 0; break; // South
	case 3: arrivalPortalNumber = 1; break; // West
	}

	for (TActorIterator<APortal> portal(world); portal; ++portal)
	{
		if (portal->GetMapNumber() == m_portals[mapNumber].number[portalNumber] && portal->GetPortalNumber() == arrivalPortalNumber)
		{
			pArrivalPortal = Cast<APortal>(*portal);
			break;
		}
	}

	return pArrivalPortal;
}