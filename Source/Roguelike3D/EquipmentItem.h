#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Engine/DataTable.h"
#include "EquipmentItem.generated.h"

UENUM(BlueprintType)
enum class EEquipmentItemCode : uint8
{
	Blade UMETA(DisplayName = "Equipment_Blade"),
	Screwdriver UMETA(DisplayName = "Equipment_Screwdriver"),
	Spanner UMETA(DisplayName = "Equipment_Spanner"),
	RedFloatRing UMETA(DisplayName = "Equipment_RedFloatRing"),
	DuckFloatRing UMETA(DisplayName = "Equipment_DuckFloatRing"),
	RubbishBinLid UMETA(DisplayName = "Equipment_RubbishBinLid"),
	Ford UMETA(DisplayName = "Equipment_Ford"),
};

UENUM(BlueprintType)
enum class EEquipmentPart : uint8
{
	Weapon UMETA(DisplayName = "Part_Weapon"),
	Armor UMETA(DisplayName = "Part_Armor"),
	Aaccessory UMETA(DisplayName = "Part_Aaccessory"),
};

USTRUCT(BlueprintType)
struct FEquipmentItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentItemCode ItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentPart Part;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ThumbnailPath;
};

UCLASS()
class ROGUELIKE3D_API AEquipmentItem : public AItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EEquipmentItemCode m_itemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FEquipmentItemData m_itemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* m_thumbnail;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:
	AEquipmentItem();

	UFUNCTION(BlueprintCallable)
	void SetItemCode(EEquipmentItemCode itemCode);

	void LoadItemData();

	UFUNCTION(BlueprintCallable)
	void SetEquip(bool bEquip);

	UFUNCTION(BlueprintCallable)
	FEquipmentItemData GetItemData() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetThumbnail() const;

	UFUNCTION(BlueprintCallable)
	float GetValue() const;

	UFUNCTION(BlueprintCallable)
	FName GetSocketName() const;
};
