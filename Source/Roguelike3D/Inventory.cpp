#include "Inventory.h"
#include "EquipmentItem.h"

UInventory::UInventory()
{
	m_listUpdate = false;

	m_coin = 0;

	m_items.Init(nullptr, 12);

	m_weapon = nullptr;
	m_armor = nullptr;
	m_aaccessory = nullptr;
}

bool UInventory::IsListUpdate() const
{
	return m_listUpdate;
}

TArray<AItem*> UInventory::GetItems() const
{
	return m_items;
}

int32 UInventory::GetCoin() const
{
	return m_coin;
}

AItem* UInventory::GetWeapon() const
{
	return m_weapon;
}

AItem* UInventory::GetArmor() const
{
	return m_armor;
}

AItem* UInventory::GetAaccessory() const
{
	return m_aaccessory;
}

void UInventory::FinishListUpdate()
{
	m_listUpdate = false;
}

void UInventory::ObtainCoin(int32 value)
{
	m_coin += value;
}

bool UInventory::SpendCoin(int32 value)
{
	if (value >= m_coin)
	{
		m_coin -= value;
		return true;
	}
	
	return false;
}

void UInventory::Equip(AItem* newItem, USkeletalMeshComponent* pPlayerMesh)
{
	AEquipmentItem* pEquipmentItem = Cast<AEquipmentItem>(newItem);
	pEquipmentItem->SetEquip(true);
	FEquipmentItemData newItemData = pEquipmentItem->GetItemData();

	switch (newItemData.Part)
	{
	case EEquipmentPart::Weapon: 
	{
		if (m_weapon)
		{
			AEquipmentItem* pOldEquipmentItem = Cast<AEquipmentItem>(m_weapon);
			pOldEquipmentItem->SetEquip(false);
			pOldEquipmentItem->AttachToComponent(pPlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), pOldEquipmentItem->GetSocketName());
			m_items.Add(m_weapon); 
		}
		m_weapon = newItem;
		break;
	}
	case EEquipmentPart::Armor:
	{
		if (m_armor)
		{
			AEquipmentItem* pOldEquipmentItem = Cast<AEquipmentItem>(m_armor);
			pOldEquipmentItem->SetEquip(false);
			pOldEquipmentItem->AttachToComponent(pPlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), pOldEquipmentItem->GetSocketName());
			m_items.Add(m_armor);
		}
		m_armor = newItem; 
		break;
	}
	case EEquipmentPart::Aaccessory:
	{
		if (m_aaccessory)
		{
			AEquipmentItem* pOldEquipmentItem = Cast<AEquipmentItem>(m_aaccessory);
			pOldEquipmentItem->SetEquip(false);
			pOldEquipmentItem->AttachToComponent(pPlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), pOldEquipmentItem->GetSocketName());
			m_items.Add(m_aaccessory);
		}
		m_aaccessory = newItem;
		break;
	}
	}

	m_items.Remove(newItem);

	m_listUpdate = true;
}

void UInventory::AddItem(AItem* newItem)
{
	for (auto &inventorySlot : m_items)
	{
		if (inventorySlot == nullptr)
		{
			inventorySlot = newItem;
			break;
		}
	}
}

float UInventory::GetWeaponValue() const
{
	if (!m_weapon) return 0;

	AEquipmentItem* pEquipmentItem = Cast<AEquipmentItem>(m_weapon);
	return pEquipmentItem->GetValue();
}

float UInventory::GetArmorValue() const
{
	if (!m_armor) return 0;

	AEquipmentItem* pEquipmentItem = Cast<AEquipmentItem>(m_armor);
	return pEquipmentItem->GetValue();
}

float UInventory::GetAaccessoryValue() const
{
	if (!m_aaccessory) return 0;

	AEquipmentItem* pEquipmentItem = Cast<AEquipmentItem>(m_aaccessory);
	return pEquipmentItem->GetValue();
}