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

USTRUCT(BlueprintType)
struct FEquipmentItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentItemCode ItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StaticMeshPath;
};

UCLASS()
class ROGUELIKE3D_API AEquipmentItem : public AItem
{
	GENERATED_BODY()
	
protected:


public:
	AEquipmentItem();

	virtual void Tick(float DeltaTime) override;
};
