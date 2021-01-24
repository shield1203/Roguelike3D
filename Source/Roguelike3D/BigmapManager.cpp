#include "BigmapManager.h"

UBigmapManager::UBigmapManager()
{
	CheckVisitedBlocks(0, 0, 0);
}
 
TMap<int32, FIntPoint> UBigmapManager::GetVisitedBlocks() const
{
	return m_visitedBlocks;
}

void UBigmapManager::CheckVisitedBlocks(int32 mapNumber, int32 xPos, int32 yPos)
{
	if (!m_visitedBlocks.Contains(mapNumber))
	{
		m_visitedBlocks.Add(mapNumber);
		m_visitedBlocks[mapNumber].X = 0;
		m_visitedBlocks[mapNumber].Y = 0;
	}
}