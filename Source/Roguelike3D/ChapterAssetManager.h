#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChapterAssetManager.generated.h"

UCLASS()
class ROGUELIKE3D_API UChapterAssetManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<class UStaticMesh*> m_items;

public:
	UChapterAssetManager();

	class UStaticMesh* GetItemMesh();
};
