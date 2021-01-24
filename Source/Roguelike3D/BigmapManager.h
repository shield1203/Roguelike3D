#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BigmapManager.generated.h"

UCLASS()
class ROGUELIKE3D_API UBigmapManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TMap<int32, FIntPoint> m_visitedBlocks;

public:
	UBigmapManager();

	UFUNCTION(BlueprintCallable)
	TMap<int32, FIntPoint> GetVisitedBlocks() const;

	void CheckVisitedBlocks(int32 mapNumber, int32 xPos, int32 yPos);
};
