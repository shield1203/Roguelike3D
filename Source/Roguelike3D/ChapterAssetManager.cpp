#include "ChapterAssetManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

UChapterAssetManager::UChapterAssetManager()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> CoinItem(TEXT("/Game/Else/Mesh/coin"));
	m_items.Add(CoinItem.Object);
}


UStaticMesh* UChapterAssetManager::GetItemMesh()
{
	return m_items[0];
}