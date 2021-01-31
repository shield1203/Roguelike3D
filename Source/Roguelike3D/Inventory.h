#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "Inventory.generated.h"

UCLASS()
class ROGUELIKE3D_API UInventory : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<AItem*> m_Items;

	UPROPERTY()
	AItem* m_weapon;

	UPROPERTY()
	AItem* m_armor;

	UPROPERTY()
	AItem* m_aaccessory;

public:
	UInventory();
};
