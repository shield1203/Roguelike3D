#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Engine/DataTable.h"
#include "ConsumptionItem.generated.h"

UENUM(BlueprintType)
enum class EConsumptionItemCode : uint8
{
	Coin UMETA(DisplayName = "Consumption_Coin"),
};

USTRUCT(BlueprintType)
struct FConsumptionItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConsumptionItemCode ItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StaticMeshPath;
};

UCLASS()
class ROGUELIKE3D_API AConsumptionItem : public AItem
{
	GENERATED_BODY()
	
protected:
	FConsumptionItemData m_itemData;

public:
	AConsumptionItem();

	virtual void Tick(float DeltaTime) override;
};
