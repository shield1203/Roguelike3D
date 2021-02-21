#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossPojectile.generated.h"

UCLASS()
class ROGUELIKE3D_API ABossPojectile : public AActor
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
	class UParticleSystem* m_particleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_damage;

	int32 m_hitCount;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	ABossPojectile();

	void InitializeProjectile(const FVector& direction, float damageValue);

	UFUNCTION(BlueprintCallable)
	void OnProjectileBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
