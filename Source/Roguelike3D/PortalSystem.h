#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PortalSystem.generated.h"

USTRUCT(Atomic, BlueprintType, Blueprintable)
struct FPortalNumber
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<int32> number;
};

USTRUCT(Atomic, BlueprintType, Blueprintable)
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

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROGUELIKE3D_API UPortalSystem : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	int32 m_maxMapNumber;

	UPROPERTY()
	int32 m_maxPortalCount;

	UPROPERTY()
	TArray<int32> m_remainMapNumber;

	UPROPERTY()
	TMap<int32, FPortalNumber> m_portals;

	UPROPERTY()
	TArray<FMapPos> m_mapPos;

private:
	void InitializePortalData();

	void AttachMap();

	bool IsEmptyPos(int32 xPos, int32 yPos, int32 direction);

	FIntPoint GetMapPos(int32 mapNumber);

public:
	UPortalSystem();

	void SetRandomRoguelikeMap();

	void SetArrivalPortals();

	class APortal* GetArrivalPortal(int32 mapNumber, int32 portalNumber);
};
