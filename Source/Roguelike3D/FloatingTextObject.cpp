#include "FloatingTextObject.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "ConsumptionItemWidget.h"
#include "DamageWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFloatingTextObject::AFloatingTextObject()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("FloatingTextSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_consumptionText = CreateDefaultSubobject<UWidgetComponent>(TEXT("ConsumptionWidgetComponent"));
	m_consumptionText->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UConsumptionItemWidget>ConsumptionWidget(TEXT("/Game/Widgets/Chapter/WB_Consumption"));
	if (ConsumptionWidget.Succeeded())
	{
		m_consumptionText->SetWidgetClass(ConsumptionWidget.Class);
	}
	m_consumptionText->SetWidgetSpace(EWidgetSpace::Screen);
	m_consumptionText->SetDrawSize(FVector2D(500.0f, 60.0f));
	m_consumptionText->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_consumptionText->SetVisibility(false);

	m_damageText = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidgetComponent"));
	m_damageText->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UDamageWidget>DamageWidget(TEXT("/Game/Widgets/Chapter/WB_Damage"));
	if (DamageWidget.Succeeded())
	{
		m_damageText->SetWidgetClass(DamageWidget.Class);
	}
	m_damageText->SetWidgetSpace(EWidgetSpace::Screen);
	m_damageText->SetDrawSize(FVector2D(500.0f, 60.0f));
	m_damageText->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_damageText->SetVisibility(false);
}

void AFloatingTextObject::BeginPlay()
{
	Super::BeginPlay();

}

void AFloatingTextObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloatingTextObject::InitializeConsumptionText(int32 value, FString target, float R, float G, float B)
{
	UConsumptionItemWidget* pConsumptionWidget = Cast<UConsumptionItemWidget>(m_consumptionText->GetUserWidgetObject());
	if (pConsumptionWidget)
	{
		pConsumptionWidget->SetValue(this, value, target, R, G, B);
		m_consumptionText->SetVisibility(true);
	}
}

void AFloatingTextObject::InitializeDamageText(int32 value, float R, float G, float B)
{
	UDamageWidget* pDamageWidget = Cast<UDamageWidget>(m_damageText->GetUserWidgetObject());
	if (pDamageWidget)
	{
		pDamageWidget->SetValue(this, value, R, G, B);
		m_damageText->SetVisibility(true);
	}
}