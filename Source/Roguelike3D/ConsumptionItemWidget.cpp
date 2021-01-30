#include "ConsumptionItemWidget.h"

void UConsumptionItemWidget::SetValue(AActor* OwningActor, int32 value, FString target, float R, float G, float B)
{
	m_owningActor = OwningActor;
	m_value = value;
	m_target = target;
	m_color = FSlateColor(FLinearColor(R, G, B));
}