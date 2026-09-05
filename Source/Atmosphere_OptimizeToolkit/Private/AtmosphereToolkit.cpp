#include "AtmosphereToolkit.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Engine/SkyLight.h"
#include "Engine/PostProcessVolume.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyLightComponent.h"
#include "EngineUtils.h"

void UAtmosphereToolkit::ApplyPresetData(const FAtmospherePresetData& Data)
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return;

    // Directional Light
    for (TActorIterator<ADirectionalLight> It(World); It; ++It)
    {
        ADirectionalLight* Sun = *It;
        if (Sun && Sun->GetLightComponent())
        {
            Sun->GetLightComponent()->SetIntensity(Data.SunIntensity);
            Sun->GetLightComponent()->SetLightColor(FLinearColor::MakeFromColorTemperature(Data.SunTemperature));
            Sun->SetActorRotation(Data.SunRotation);
            break;
        }
    }

    // Exponential Height Fog
    for (TActorIterator<AExponentialHeightFog> It(World); It; ++It)
    {
        AExponentialHeightFog* Fog = *It;
        if (Fog && Fog->GetComponent())
        {
            Fog->GetComponent()->SetFogDensity(Data.FogDensity);
            Fog->GetComponent()->SetFogMaxOpacity(Data.FogMaxOpacity);
            Fog->GetComponent()->SetFogHeightFalloff(Data.FogHeightFalloff);
            Fog->GetComponent()->SetStartDistance(Data.FogStartDistance);
            Fog->GetComponent()->SetVolumetricFog(Data.bEnableVolumetricFog);
            Fog->GetComponent()->SetFogInscatteringColor(Data.FogColor);
            break;
        }
    }

    // Sky Light
    for (TActorIterator<ASkyLight> It(World); It; ++It)
    {
        ASkyLight* Sky = *It;
        if (Sky && Sky->GetLightComponent())
        {
            Sky->GetLightComponent()->SetIntensity(Data.SkyLightIntensity);
            break;
        }
    }

    // Post Process Volume (UE 5.7+)
    if (World->PostProcessVolumes.Num() > 0 && World->PostProcessVolumes[0])
    {
        APostProcessVolume* PPV = Cast<APostProcessVolume>(World->PostProcessVolumes[0]);
        if (PPV)
        {
            FPostProcessSettings& Settings = PPV->Settings;

            Settings.bOverride_AutoExposureBias = true;
            Settings.AutoExposureBias = Data.ExposureBias;

            Settings.bOverride_ColorSaturation = true;
            Settings.ColorSaturation = FVector4(Data.Saturation, Data.Saturation, Data.Saturation, 1.0f);

            Settings.bOverride_ColorContrast = true;
            Settings.ColorContrast = FVector4(Data.Contrast, Data.Contrast, Data.Contrast, 1.0f);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] PostProcessVolume not found."));
    }

    UE_LOG(LogTemp, Log, TEXT("[AtmosphereToolkit] Preset applied: Sun=%.1f, Fog=%.3f, Sky=%.1f"),
        Data.SunIntensity, Data.FogDensity, Data.SkyLightIntensity);
}

TArray<FName> UAtmosphereToolkit::GetPresetRowNames()
{
    TArray<FName> Names;
    UDataTable* PresetTable = LoadObject<UDataTable>(nullptr,
        TEXT("/Game/Atmosphere_OptimizeToolkit/DT_Presets.DT_Presets"));
    if (PresetTable)
    {
        Names = PresetTable->GetRowNames();
    }
    return Names;
}

void UAtmosphereToolkit::ResetToDefault()
{
    FAtmospherePresetData DefaultData;
    DefaultData.SunIntensity = 10.0f;
    DefaultData.SunTemperature = 5500.0f;
    DefaultData.SunRotation = FRotator(-45.0f, 0.0f, 0.0f);
    DefaultData.FogDensity = 0.02f;
    DefaultData.FogMaxOpacity = 1.0f;
    DefaultData.FogHeightFalloff = 0.2f;
    DefaultData.FogStartDistance = 0.0f;
    DefaultData.bEnableVolumetricFog = false;
    DefaultData.FogColor = FLinearColor(0.5f, 0.6f, 0.8f);
    DefaultData.SkyLightIntensity = 1.0f;
    DefaultData.ExposureBias = 0.0f;
    DefaultData.Saturation = 1.0f;
    DefaultData.Contrast = 1.0f;

    ApplyPresetData(DefaultData);
}