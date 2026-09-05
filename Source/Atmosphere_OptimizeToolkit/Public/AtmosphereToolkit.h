#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "AtmosphereToolkit.generated.h"

// ============================================
// PRESET DATA STRUCT
// ============================================
USTRUCT(BlueprintType)
struct ATMOSPHERE_OPTIMIZETOOLKIT_API FAtmospherePresetData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")
    FText PresetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun")
    float SunIntensity = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun")
    float SunTemperature = 5500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun")
    FRotator SunRotation = FRotator(-45.0f, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    float FogDensity = 0.02f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    float FogMaxOpacity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    float FogHeightFalloff = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    float FogStartDistance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    bool bEnableVolumetricFog = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    FLinearColor FogColor = FLinearColor(0.5f, 0.6f, 0.8f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
    float SkyLightIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float ExposureBias = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float Saturation = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float Contrast = 1.0f;
};

// ============================================
// STATIC FUNCTIONS FOR PRESETS
// ============================================
UCLASS()
class ATMOSPHERE_OPTIMIZETOOLKIT_API UAtmosphereToolkit : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    static void ApplyPresetData(const FAtmospherePresetData& Data);

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    static TArray<FName> GetPresetRowNames();

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    static void ResetToDefault();
};