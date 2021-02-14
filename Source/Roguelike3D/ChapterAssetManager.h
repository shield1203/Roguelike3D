#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChapterAssetManager.generated.h"

class UStaticMesh;
class AEnemyBase;

UCLASS()
class ROGUELIKE3D_API UChapterAssetManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UStaticMesh*> m_consumptionItemStaticMesh;

	UPROPERTY()
	TArray<UStaticMesh*> m_equipmentItemStaticMesh;

	UPROPERTY()
	TArray<TSubclassOf<AEnemyBase>> m_enemyBlueprint;

public:
	UChapterAssetManager();

	UStaticMesh* GetConsumptionItemMesh(uint8 ItemCode) const;

	UStaticMesh* GetEquipmentItemMesh(uint8 ItemCode) const;

	TSubclassOf<AEnemyBase> GetEnemyBlueprintClass(uint8 EnemyCode) const;
};
