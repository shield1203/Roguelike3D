#include "EquipmentItem.h"
#include "Engine/Texture2D.h"

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
}

void AEquipmentItem::LoadItemData()
{

}

class UTexture2D* AEquipmentItem::GetThumbnail() const
{
	return m_thumbnail;
}