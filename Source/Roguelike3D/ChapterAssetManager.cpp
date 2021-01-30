#include "ChapterAssetManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

UChapterAssetManager::UChapterAssetManager()
{
	TArray<FString> strAssetPath;
	strAssetPath.Add(TEXT("/Game/Else/Mesh/coin"));
	strAssetPath.Add(TEXT("/Game/PolygonCity/Meshes/Props/SM_Prop_LargeSign_Milkshake_01"));
	strAssetPath.Add(TEXT("/Game/PolygonCity/Meshes/Props/SM_Prop_LargeSign_Donut_01"));

	for (auto consumptionItemPath : strAssetPath)
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> ConsumptionItem(*consumptionItemPath);
		m_consumptionItemStaticMesh.Add(ConsumptionItem.Object);
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