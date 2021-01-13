#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class ROGUELIKE3D_API APortal : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Portal, meta = (AllowPrivateAccess = "true"))
	int32 m_mapNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Portal, meta = (AllowPrivateAccess = "true"))
	int32 m_partalNumber;

protected:
	virtual void BeginPlay() override;

public:	
	APortal();

	virtual void Tick(float DeltaTime) override;

};
