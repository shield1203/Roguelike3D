#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PortalSystem.generated.h"

USTRUCT()
struct FMapPos
{
	GENERATED_USTRUCT_BODY()

	FMapPos(int32 map = 0, int32 x = 0, int32 y = 0) : mapNumber(map), xPos(x), yPos(y){}

public:
	UPROPERTY()
	int32 mapNumber;

	UPROPERTY()
	int32 xPos;

	UPROPERTY()
	int32 yPos;
};

UCLASS()
class ROGUELIKE3D_API UPortalSystem : public UObject
{
	GENERATED_BODY()
	
private:
	int32 m_maxMapNumber;

	int32 m_maxPortalCount;

	TArray<int32> m_remainMapNumber;

	TMap<int32, TArray<int32>> m_portals;

	TArray<FMapPos> m_mapPos;

private:
	void InitializePortalData();

	void AttachMap();

	bool IsEmptyPos(int32 xPos, int32 yPos, int32 direction);

public:
	UPortalSystem();

	void SetRandomRoguelikeMap();

	class APortal* GetArrivalPortal(int32 mapNumber, int32 portalNumber);
};
