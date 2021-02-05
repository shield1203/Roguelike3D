#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentItem.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class ROGUELIKE3D_API APlayerProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* m_collisionComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* m_staticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* m_projectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	class UMaterialInterface* m_materialInstance;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystem* m_particleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EEquipmentItemCode m_itemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_damage;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	APlayerProjectile();

	void InitializePlayerProjectile(const FVector& direction, EEquipmentItemCode itemCode, float damageValue);

	UFUNCTION(BlueprintCallable)
	void OnProjectileBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};