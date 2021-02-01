#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "Inventory.generated.h"

class AItem;

UCLASS()
class ROGUELIKE3D_API UInventory : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	bool m_listUpdate;

	UPROPERTY()
	int32 m_coin;

	UPROPERTY()
	TArray<AItem*> m_items;

	UPROPERTY()
	AItem* m_weapon;

	UPROPERTY()
	AItem* m_armor;

	UPROPERTY()
	AItem* m_aaccessory;

public:
	UInventory();

	UFUNCTION(BlueprintCallable)
	TArray<AItem*> GetItems() const;

	UFUNCTION(BlueprintCallable)
	bool IsListUpdate() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCoin() const;

	UFUNCTION(BlueprintCallable)
	AItem* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	AItem* GetArmor() const;

	UFUNCTION(BlueprintCallable)
	AItem* GetAaccessory() const;

	UFUNCTION(BlueprintCallable)
	void FinishListUpdate();

	UFUNCTION(BlueprintCallable)
	void ObtainCoin(int32 value);

	UFUNCTION(BlueprintCallable)
	bool SpendCoin(int32 value);

	float GetWeaponValue() const;

	float GetArmorValue() const;

	float GetAaccessoryValue() const;

	UFUNCTION(BlueprintCallable)
	void Equip(AItem* newItem, class USkeletalMeshComponent* pPlayerMesh);

	UFUNCTION(BlueprintCallable)
	void AddItem(AItem* newItem);
};
