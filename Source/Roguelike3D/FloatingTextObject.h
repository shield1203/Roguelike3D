#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingTextObject.generated.h"

UCLASS()
class ROGUELIKE3D_API AFloatingTextObject : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* m_consumptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* m_damageText;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:	
	AFloatingTextObject();
	
	
	void InitializeConsumptionText(int32 value, FString target, float R, float G, float B);

	void InitializeDamageText(int32 value, float R, float G, float B);
};
