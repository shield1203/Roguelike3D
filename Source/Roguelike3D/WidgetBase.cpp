#include "WidgetBase.h"

void UWidgetBase::SetOwningActor(AActor* OwningActor)
{
	m_owningActor = OwningActor;
}

void UWidgetBase::SetColor(float R, float G, float B)
{
	m_color = FSlateColor(FLinearColor(R, G, B));
}