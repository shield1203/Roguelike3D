#include "DamageWidget.h"

void UDamageWidget::SetValue(AActor* OwningActor, int32 value, float R, float G, float B)
{
	m_owningActor = OwningActor;
	m_value = value;
	m_color = FSlateColor(FLinearColor(R, G, B));
}