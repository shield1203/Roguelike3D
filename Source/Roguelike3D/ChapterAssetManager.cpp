#include "ChapterAssetManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"

UChapterAssetManager::UChapterAssetManager()
{
	TArray<FString> strConsumptionItemAssetPath;
	strConsumptionItemAssetPath.Add(TEXT("/Game/Else/Mesh/coin"));
	strConsumptionItemAssetPath.Add(TEXT("/Game/PolygonCity/Meshes/Props/SM_Prop_LargeSign_Milkshake_01"));
	strConsumptionItemAssetPath.Add(TEXT("/Game/PolygonCity/Meshes/Props/SM_Prop_LargeSign_Donut_01"));

	for (auto consumptionItemPath : strConsumptionItemAssetPath)
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> ConsumptionItem(*consumptionItemPath);
		m_consumptionItemStaticMesh.Add(ConsumptionItem.Object);
	}

	TArray<FString> strEquipmentAssetPath;
	strEquipmentAssetPath.Add(TEXT("/Game/PolygonTown/Meshes/Items/SM_Item_Blade_01"));
	strEquipmentAssetPath.Add(TEXT("/Game/PolygonTown/Meshes/Items/SM_Item_Screwdriver_01"));
	strEquipmentAssetPath.Add(TEXT("/Game/PolygonTown/Meshes/Items/SM_Item_Spanner_01"));
	strEquipmentAssetPath.Add(TEXT("/Game/PolygonTown/Meshes/Props/SM_Prop_Pool_Float_Ring_01"));
	strEquipmentAssetPath.Add(TEXT("/Game/PolygonTown/Meshes/Props/SM_Prop_Pool_Float_Ring_04"));
	strEquipmentAssetPath.Add(TEXT("/Game/PolygonTown/Meshes/Props/SM_Prop_RubbishBin_01_Lid"));
	strEquipmentAssetPath.Add(TEXT("/Game/AutomotiveMaterials/LevelAssets/PreviewMeshes/SM_Shaderball"));
	
	for (auto equipmentItemPath : strEquipmentAssetPath)
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> EquipmentItem(*equipmentItemPath);
		m_equipmentItemStaticMesh.Add(EquipmentItem.Object);
	}

	TArray<FString> strEnemyBlueprintPath;
	strEnemyBlueprintPath.Add(TEXT("/Game/Blueprints/Enemy/Grim/BP_Grim_White"));
	strEnemyBlueprintPath.Add(TEXT("/Game/Blueprints/Enemy/Grim/BP_Grim_Red"));
	strEnemyBlueprintPath.Add(TEXT("/Game/Blueprints/Enemy/Grim/BP_Grim_Green"));

	for (auto enemyBlueprintPath : strEnemyBlueprintPath)
	{
		ConstructorHelpers::FClassFinder<AEnemyBase> EnemyBlueprint(*enemyBlueprintPath);
		if (EnemyBlueprint.Succeeded())
		{
			m_enemyBlueprint.Add(EnemyBlueprint.Class);
		}
	}
}


UStaticMesh* UChapterAssetManager::GetConsumptionItemMesh(uint8 ItemCode) const
{
	return m_consumptionItemStaticMesh[ItemCode];
}

UStaticMesh* UChapterAssetManager::GetEquipmentItemMesh(uint8 ItemCode) const
{
	return m_equipmentItemStaticMesh[ItemCode];
}

TSubclassOf<AEnemyBase> UChapterAssetManager::GetEnemyBlueprintClass(uint8 EnemyCode) const
{
	return m_enemyBlueprint[EnemyCode];
}