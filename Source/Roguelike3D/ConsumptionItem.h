#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Engine/DataTable.h"
#include "ConsumptionItem.generated.h"

UENUM(BlueprintType)
enum class EConsumptionItemCode : uint8
{
	Coin UMETA(DisplayName = "Consumption_Coin"),
	Milkshake UMETA(DisplayName = "Consumption_Milkshake"),
	Donut UMETA(DisplayName = "Consumption_Donut"),
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
	FString Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float G;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float B;
};

UCLASS()
class ROGUELIKE3D_API AConsumptionItem : public AItem
{
	GENERATED_BODY()
	
protected:
	bool m_use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* m_valueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EConsumptionItemCode m_itemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FConsumptionItemData m_itemData;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:
	AConsumptionItem();

	UFUNCTION(BlueprintCallable)
	void SetItemCode(EConsumptionItemCode itemCode);

	UFUNCTION(BlueprintCallable)
	void LoadItemData();

	UFUNCTION(BlueprintCallable)
	void OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
