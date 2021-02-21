#include "BossStagePortal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "ChapterGameMode.h"

ABossStagePortal::ABossStagePortal()
{
	PrimaryActorTick.bCanEverTick = false;

	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("BossPortalInputComponent"));
	InputComponent->BindKey(EKeys::F, EInputEvent::IE_Pressed, this, &ABossStagePortal::OnPressButton);

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("BossPortalSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossPortalStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PortalVisualAsset(TEXT("/Game/TandP/Teleportation/Mesh/SM_BossPortal"));
	if (PortalVisualAsset.Succeeded())
	{
		m_staticMeshComponent->SetStaticMesh(PortalVisualAsset.Object);
	}

	m_collisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BossPortalCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetCapsuleHalfHeight(200.f);
	m_collisionComponent->SetCapsuleRadius(20.f);
	m_collisionComponent->SetGenerateOverlapEvents(true);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossStagePortal::OnPlayerBeginOverlap);
	m_collisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABossStagePortal::OnPlayerEndOverlap);

	m_buttonWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BossPortalButtonComponent"));
	m_buttonWidgetComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget> PortalButtonWidget(TEXT("/Game/Widgets/Chapter/WB_PortalButton"));
	if (PortalButtonWidget.Succeeded())
	{
		m_buttonWidgetComponent->SetWidgetClass(PortalButtonWidget.Class);
	}
	m_buttonWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_buttonWidgetComponent->SetDrawSize(FVector2D(50.f, 50.0f));
	m_buttonWidgetComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	m_buttonWidgetComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 51.0f));
	m_buttonWidgetComponent->RegisterComponent();

	SetActivation(false);
}

void ABossStagePortal::BeginPlay()
{
	Super::BeginPlay();
	
	m_buttonWidgetComponent->SetVisibility(false);
}

void ABossStagePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossStagePortal::SetActivation(bool bActivation)
{
	m_activation = bActivation;
}

void ABossStagePortal::OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!m_activation) return;

	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr)
	{
		m_buttonWidgetComponent->SetVisibility(true);
		EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
}

void ABossStagePortal::OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr)
	{
		m_buttonWidgetComponent->SetVisibility(false);
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
}

void ABossStagePortal::OnPressButton()
{
	if (!m_activation) return;

	ARoguelike3DCharacter* pPlayer = Cast<ARoguelike3DCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (pPlayer != nullptr)
	{
		pPlayer->SetActorLocation(m_arrivalLocation);

		UWorld* pWorld = GetWorld();
		if (pWorld)
		{
			AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
			if (pGameMode)
			{
				pGameMode->SetCurMapNumber(-1, 0, 0);
			}
		}
	}
}