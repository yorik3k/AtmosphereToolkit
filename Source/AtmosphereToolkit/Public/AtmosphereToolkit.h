#pragma once
// Atm.Toolkit.h
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "AtmosphereToolkit.generated.h"

// ============================================
// PRESSET DATA STRUCT
// ============================================
USTRUCT(BlueprintType)
struct ATMOSPHERETOOLKIT_API FAtmospherePresetData : public FTableRowBase
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
    // Ex.Fog category
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
    /// 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
    float SkyLightIntensity = 1.0f;
    /// <summary>
    /// Post Process Volume
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float ExposureBias = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float Saturation = 1.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float Contrast = 1.0f;
};

// ============================================
// DATA ASSET FOR SAVED PRESSETS
// ============================================
UCLASS(BlueprintType)
class ATMOSPHERETOOLKIT_API UAtmospherePreset : public UDataAsset
{
    GENERATED_BODY()

public:
    /// <summary>
    /// Sun
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sun")
    float SunIntensity = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sun")
    float SunTemperature = 5500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sun")
    FRotator SunRotation = FRotator(-45.0f, 0.0f, 0.0f);

    // Ex.Fog category
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
    /// 

    /// <summary>
    /// Sky
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sky")
    float SkyLightIntensity = 1.0f;

    /// <summary>
    /// Post Process Volume
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float ExposureBias = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float Saturation = 1.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPV")
    float Contrast = 1.0f;

    UFUNCTION(CallInEditor, Category = "Actions")
    void ApplyToCurrentLevel();

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    static void ApplyPresetData(const FAtmospherePresetData& Data);

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    static TArray<FName> GetPresetRowNames();
};

// ============================================
// лндскэ
// ============================================
class FAtmosphereToolkitModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};