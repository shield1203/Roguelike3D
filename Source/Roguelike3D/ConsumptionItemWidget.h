#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConsumptionItemWidget.generated.h"

class AActor;

UCLASS()
class ROGUELIKE3D_API UConsumptionItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* m_owningActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateColor m_color;

public:
	void SetValue(AActor* OwningActor, int32 value, FString target, float R, float G, float B);
};
