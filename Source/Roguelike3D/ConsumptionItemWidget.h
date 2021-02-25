#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "ConsumptionItemWidget.generated.h"

UCLASS()
class ROGUELIKE3D_API UConsumptionItemWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_target;

public:
	void SetValue(AActor* OwningActor, int32 value, FString target, float R, float G, float B);
};
