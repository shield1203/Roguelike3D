#include "BossSkillObject.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"

ABossSkillObject::ABossSkillObject()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("BossSkillObjectSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("BossSkillObjectDecalComponent"));
	m_decalComponent->SetupAttachment(RootComponent);
	m_decalComponent->SetRelativeRotation(FRotator(270.f, 0.0f, 0.0f).Quaternion());
	m_decalComponent->DecalSize = FVector(100.0f, 200.0f, 200.0f);
	static ConstructorHelpers::FObjectFinder<UMaterial>CircleRangeMaterial(TEXT("Material'/Game/Resource/MT_CircleRange.MT_CircleRange'"));
	if (CircleRangeMaterial.Succeeded())
	{
		m_decalComponent->SetMaterial(0, CircleRangeMaterial.Object);
	}
	m_decalComponent->CreateDynamicMaterialInstance();

	m_maxValue = 0.4f;
}

void ABossSkillObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossSkillObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

