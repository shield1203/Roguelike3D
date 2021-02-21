#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class ROGUELIKE3D_API APortal : public AActor
{
	GENERATED_BODY()
	
protected:
	bool m_activation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal, meta = (AllowPrivateAccess = "true"))
	int32 m_mapNumber;

	int32 m_mapXPos;

	int32 m_mapYPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal, meta = (AllowPrivateAccess = "true"))
	int32 m_portalNumber;

	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* m_staticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* m_collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* m_particleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* m_buttonWidgetComponent;

	UPROPERTY()
	APortal* m_arrivalPortal;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:	
	APortal();

	FORCEINLINE	int32 GetMapNumber() const { return m_mapNumber; }

	FORCEINLINE	int32 GetPortalNumber() const { return m_portalNumber; };

	FORCEINLINE	int32 GetMapXPos() const { return m_mapXPos; };

	FORCEINLINE	int32 GetMapYPos() const { return m_mapYPos; };

	void SetArrivalPortal(APortal* ArrivalPortal, int32 xPos, int32 yPos);

	void SetActivation(bool bActivation);

	UFUNCTION(BlueprintCallable)
	void OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OnPressButton();
};