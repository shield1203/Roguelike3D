#include "EquipmentItem.h"
#include "Components/BoxComponent.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "ChapterAssetManager.h"
#include "ChapterGameMode.h"
#include "Roguelike3DCharacter.h"

AEquipmentItem::AEquipmentItem()
{
	PrimaryActorTick.bCanEverTick = false;

	
}

void AEquipmentItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AEquipmentItem::BeginPlay()
{
	Super::BeginPlay();

}

void AEquipmentItem::SetItemCode(EEquipmentItemCode itemCode)
{
	m_itemCode = itemCode;

	LoadItemData();
}

void AEquipmentItem::LoadItemData()
{
	UDataTable* pItemDataTable = LoadObject<UDataTable>(this, TEXT("/Game/DataTable/EquipmentItem"));
	FEquipmentItemData* pItemData = pItemDataTable->FindRow<FEquipmentItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_itemCode)))), FString(""));
	m_itemData.ItemCode = m_itemCode;
	m_itemData.Part = pItemData->Part;
	m_itemData.Value = pItemData->Value;
	m_itemData.Name = pItemData->Name;
	m_itemData.SocketName = pItemData->SocketName;
	m_itemData.Explanation = pItemData->Explanation;
	m_thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *pItemData->ThumbnailPath));

	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (pGameMode)
		{
			m_staticMeshComponent->SetStaticMesh(pGameMode->GetChapterAssetManager()->GetEquipmentItemMesh(static_cast<uint8>(m_itemCode)));
			m_staticMeshComponent->SetVisibility(false);
		}
	}
}

void AEquipmentItem::SetEquip(bool bEquip)
{
	switch (m_itemData.Part)
	{
	case EEquipmentPart::Armor:
	case EEquipmentPart::Aaccessory: 
	{
		m_staticMeshComponent->SetVisibility(bEquip); 

		break;
	}
	}
}

FEquipmentItemData AEquipmentItem::GetItemData() const
{
	return m_itemData;
}

EEquipmentItemCode AEquipmentItem::GetItemCode() const
{
	return m_itemCode;
}

class UTexture2D* AEquipmentItem::GetThumbnail() const
{
	return m_thumbnail;
}

float AEquipmentItem::GetValue() const
{
	return m_itemData.Value;
}

FName AEquipmentItem::GetSocketName() const
{
	return m_itemData.SocketName;
}