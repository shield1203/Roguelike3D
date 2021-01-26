#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class ROGUELIKE3D_API AItem : public AActor
{
	GENERATED_BODY()
	
protected:	
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* m_staticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* m_collisionComponent;

protected:
	virtual void BeginPlay() override;

public:	
	AItem();

	virtual void Tick(float DeltaTime) override;

};
