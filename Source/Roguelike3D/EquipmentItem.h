#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Engine/DataTable.h"
#include "EquipmentItem.generated.h"

UENUM(BlueprintType)
enum class EEquipmentItemCode : uint8
{
	Port UMETA(DisplayName = "Equipment_Port"),
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
	class UTexture2D* GetThumbnail() const;
};
