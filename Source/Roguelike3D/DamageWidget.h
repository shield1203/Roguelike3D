#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "DamageWidget.generated.h"

UCLASS()
class ROGUELIKE3D_API UDamageWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_value;
public:
	void SetValue(AActor* OwningActor, int32 value, float R, float G, float B);
};
