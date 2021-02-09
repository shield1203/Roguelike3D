#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.h"
#include "EnemySpawnPlace.generated.h"

UCLASS()
class ROGUELIKE3D_API AEnemySpawnPlace : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawnPlace, meta = (AllowPrivateAccess = "true"))
	EEnemyCode m_spawnEnemyCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawnPlace, meta = (AllowPrivateAccess = "true"))
	int32 m_mapNumber;

	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* m_particleComponent;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	AEnemySpawnPlace();

	UFUNCTION(BlueprintCallable)
	void OnPlayerInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
