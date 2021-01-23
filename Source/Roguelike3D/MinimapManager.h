#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "MinimapManager.generated.h"

USTRUCT(BlueprintType)
struct FMinimapData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MapNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MinimapPath;
};

USTRUCT(BlueprintType)
struct FMinimapInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* MinimapTexture;
};

UCLASS()
class ROGUELIKE3D_API UMinimapManager : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<int32, FMinimapInfo> m_MinimapData;

public:
	UMinimapManager();

	UFUNCTION(BlueprintCallable)
	FVector2D GetPlayerIconLocation(int32 mapNumber);

	UFUNCTION(BlueprintCallable)
	FVector2D GetPortalIconLocation(int32 mapNumber, int32 portalNumber);

	UFUNCTION(BlueprintCallable)
	FVector2D GetMinimapTextureSize(int32 mapNumber);

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetMinimaptexture(int32 mapNumber) const;
};
