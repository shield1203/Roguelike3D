#include "Portal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelike3DCharacter.h"
#include "ChapterGameMode.h"
#include "PortalSystem.h"
#include "GameFramework/PlayerController.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("PortalInputComponent"));
	InputComponent->BindKey(EKeys::F, EInputEvent::IE_Pressed, this, &APortal::OnPressButton);

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("PortalSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PortalVisualAsset(TEXT("/Game/TandP/Teleportation/Mesh/SM_Teleportation"));
	if (PortalVisualAsset.Succeeded())
	{
		m_staticMeshComponent->SetStaticMesh(PortalVisualAsset.Object);
	}
	m_staticMeshComponent->CreateDynamicMaterialInstance(1);

	m_collisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PortalCollisionComponent"));
	m_collisionComponent->SetupAttachment(RootComponent);
	m_collisionComponent->SetCapsuleHalfHeight(200.f);
	m_collisionComponent->SetCapsuleRadius(20.f);
	m_collisionComponent->SetGenerateOverlapEvents(true);
	m_collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnPlayerBeginOverlap);
	m_collisionComponent->OnComponentEndOverlap.AddDynamic(this, &APortal::OnPlayerEndOverlap);

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticleComponent"));
	m_particleComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PortalParticleAsset(TEXT("/Game/TandP/Teleportation/Particle/P_Teleportation"));
	if (PortalParticleAsset.Succeeded())
	{
		m_particleComponent->SetTemplate(PortalParticleAsset.Object);
	}

	m_buttonWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PortalButtonComponent"));
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

	m_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PortalAudioComponent"));
	static ConstructorHelpers::FObjectFinder<USoundCue>PortalSound(TEXT("SoundCue'/Game/Resource/Sound/Portal_Cue.Portal_Cue'"));
	if (PortalSound.Succeeded())
	{
		m_audioComponent->SetSound(PortalSound.Object);
	}
	m_audioComponent->bAutoActivate = false;

	SetActivation(false);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	m_particleComponent->SetActive(false);
	m_buttonWidgetComponent->SetVisibility(false);
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortal::SetArrivalPortal(APortal* ArrivalPortal, int32 xPos, int32 yPos)
{
	m_arrivalPortal = ArrivalPortal;
	m_mapXPos = xPos;
	m_mapYPos = yPos;
	
	if (m_arrivalPortal == nullptr) Destroy();
}

void APortal::SetActivation(bool bActivation)
{
	m_activation = bActivation;

	if (m_activation)
	{
		m_staticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.f, 0.857146f, 0));
	}
	else
	{
		m_staticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.f, 0, 0));
	}
}

void APortal::OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!m_activation) return;

	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr)
	{
		m_buttonWidgetComponent->SetVisibility(true);

		EnableInput(Cast<APlayerController>(pPlayerPawn->GetController()));

		m_particleComponent->SetActive(true);
	}
}

void APortal::OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARoguelike3DCharacter* pPlayerPawn = Cast<ARoguelike3DCharacter>(OtherActor);

	if (pPlayerPawn != nullptr)
	{
		m_buttonWidgetComponent->SetVisibility(false);
		DisableInput(Cast<APlayerController>(pPlayerPawn->GetController()));

		m_particleComponent->SetActive(false);
	}
}

void APortal::OnPressButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Is Work"));

	if (!m_activation) return;

	ARoguelike3DCharacter* pPlayer = Cast<ARoguelike3DCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (pPlayer != nullptr)
	{
		FVector destinationLocation = m_arrivalPortal->GetActorLocation();
		destinationLocation.Z += 50.f;
		pPlayer->SetActorLocation(destinationLocation);

		m_audioComponent->Play();

		UWorld* pWorld = GetWorld();
		if (pWorld)
		{
			AChapterGameMode* pGameMode = Cast<AChapterGameMode>(UGameplayStatics::GetGameMode(pWorld));
			if (pGameMode)
			{
				pGameMode->SetCurMapNumber(m_arrivalPortal->GetMapNumber(), m_arrivalPortal->GetMapXPos(), m_arrivalPortal->GetMapYPos());
			}
		}
	}
}