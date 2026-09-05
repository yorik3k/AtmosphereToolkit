#include "AtmosphereEditorWidget.h"
#include "AtmosphereToolkit.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Engine/SkyLight.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/DataTable.h"
#include "EngineUtils.h"
#include "Components/EditableText.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/LightComponent.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

// ============================================
// NATIVE CONSTRUCT
// ============================================
void UAtmosphereEditorWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] NativeConstruct() CALLED!"));
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));

    // ============================================
    // BUTTONS BINDING
    // ============================================

    // Button_ApplyManual
    if (Button_ApplyManual)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Button_ApplyManual found!"));
        Button_ApplyManual->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnApplyManualClicked);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ Button_ApplyManual is NULL!"));
    }

    // ResetDefaultButton
    if (ResetDefaultButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ ResetDefaultButton found!"));
        ResetDefaultButton->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnResetDefaultClicked);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ ResetDefaultButton is NULL!"));
    }

    // Button_Apply_1
    if (Button_Apply_1)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Button_Apply_1 found!"));
        Button_Apply_1->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnPreset1Clicked);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ Button_Apply_1 is NULL!"));
    }

    // Button_Apply_2
    if (Button_Apply_2)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Button_Apply_2 found!"));
        Button_Apply_2->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnPreset2Clicked);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ Button_Apply_2 is NULL!"));
    }

    // Button_Apply_3
    if (Button_Apply_3)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Button_Apply_3 found!"));
        Button_Apply_3->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnPreset3Clicked);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ Button_Apply_3 is NULL!"));
    }

    // Button_Apply (4-я кнопка)
    if (Button_Apply)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Button_Apply (4th) found!"));
        Button_Apply->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnPreset4Clicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ⚠️ Button_Apply (4th) is NULL (optional)"));
    }

    // Button_Apply_4 (5-я кнопка)
    if (Button_Apply_4)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Button_Apply_4 (5th) found!"));
        Button_Apply_4->OnClicked.AddDynamic(this, &UAtmosphereEditorWidget::OnPreset5Clicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ⚠️ Button_Apply_4 (5th) is NULL (optional)"));
    }

    // Load Preset Table
    LoadPresetTable();

    // Load Current Settings
    LoadCurrentSettings();

    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] NativeConstruct() COMPLETED!"));
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));
}

// ============================================
// LOAD CURRENT SETTINGS
// ============================================
void UAtmosphereEditorWidget::LoadCurrentSettings()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] LoadCurrentSettings() called..."));

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] No World!"));
        return;
    }

    // Directional Light
    for (TActorIterator<ADirectionalLight> It(World); It; ++It)
    {
        ADirectionalLight* Sun = *It;
        if (Sun && Sun->GetLightComponent())
        {
            SetInputText(SunIntensityInput, Sun->GetLightComponent()->Intensity);
            SetInputText(SunTemperatureInput, Sun->GetLightComponent()->Temperature);
            SetInputText(SunPitchInput, Sun->GetActorRotation().Pitch);
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Sun found: Intensity=%.1f, Temp=%.1f"),
                Sun->GetLightComponent()->Intensity, Sun->GetLightComponent()->Temperature);
            break;
        }
    }

    // Fog
    for (TActorIterator<AExponentialHeightFog> It(World); It; ++It)
    {
        AExponentialHeightFog* Fog = *It;
        if (Fog && Fog->GetComponent())
        {
            SetInputText(FogDensityInput, Fog->GetComponent()->FogDensity);
            SetInputText(FogHeightFalloffInput, Fog->GetComponent()->FogHeightFalloff);
            SetInputText(FogMaxOpacityInput, Fog->GetComponent()->FogMaxOpacity);
            SetInputText(FogStartDistanceInput, Fog->GetComponent()->StartDistance);
            SetCheckBoxChecked(VolumetricFogCheckbox, Fog->GetComponent()->bEnableVolumetricFog);
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Fog found: Density=%.3f"), Fog->GetComponent()->FogDensity);
            break;
        }
    }

    // Sky Light
    for (TActorIterator<ASkyLight> It(World); It; ++It)
    {
        ASkyLight* Sky = *It;
        if (Sky && Sky->GetLightComponent())
        {
            SetInputText(SkyIntensityInput, Sky->GetLightComponent()->Intensity);
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] SkyLight found: Intensity=%.1f"), Sky->GetLightComponent()->Intensity);
            break;
        }
    }

    // Post Process Volume
    if (World->PostProcessVolumes.Num() > 0 && World->PostProcessVolumes[0])
    {
        APostProcessVolume* PPV = Cast<APostProcessVolume>(World->PostProcessVolumes[0]);
        if (PPV)
        {
            const FPostProcessSettings& Settings = PPV->Settings;
            SetInputText(ExposureBiasInput, Settings.AutoExposureBias);
            SetInputText(SaturationInput, Settings.ColorSaturation.X);
            SetInputText(ContrastInput, Settings.ColorContrast.X);
            SetCheckBoxChecked(UnboundCheckBox, PPV->bUnbound);
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] PPV found: Exposure=%.1f"), Settings.AutoExposureBias);
        }
    }

    ShowNotification(TEXT("Loaded current scene settings"), 1.5f);
}

// ============================================
// APPLY MANUAL SETTINGS
// ============================================
void UAtmosphereEditorWidget::ApplyManualSettings()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ApplyManualSettings() called!"));

    FAtmospherePresetData Data;
    Data.SunIntensity = GetFloatFromInput(SunIntensityInput, 10.0f);
    Data.SunTemperature = GetFloatFromInput(SunTemperatureInput, 5500.0f);
    Data.SunRotation = FRotator(GetFloatFromInput(SunPitchInput, -45.0f), 0.0f, 0.0f);
    Data.FogDensity = GetFloatFromInput(FogDensityInput, 0.02f);
    Data.FogHeightFalloff = GetFloatFromInput(FogHeightFalloffInput, 0.2f);
    Data.FogMaxOpacity = GetFloatFromInput(FogMaxOpacityInput, 1.0f);
    Data.FogStartDistance = GetFloatFromInput(FogStartDistanceInput, 0.0f);
    Data.bEnableVolumetricFog = VolumetricFogCheckbox ? VolumetricFogCheckbox->IsChecked() : false;
    Data.SkyLightIntensity = GetFloatFromInput(SkyIntensityInput, 1.0f);
    Data.ExposureBias = GetFloatFromInput(ExposureBiasInput, 0.0f);
    Data.Saturation = GetFloatFromInput(SaturationInput, 1.0f);
    Data.Contrast = GetFloatFromInput(ContrastInput, 1.0f);

    UAtmosphereToolkit::ApplyPresetData(Data);

    if (UnboundCheckBox)
    {
        UWorld* World = GEditor->GetEditorWorldContext().World();
        if (World && World->PostProcessVolumes.Num() > 0 && World->PostProcessVolumes[0])
        {
            APostProcessVolume* PPV = Cast<APostProcessVolume>(World->PostProcessVolumes[0]);
            if (PPV)
            {
                PPV->bUnbound = UnboundCheckBox->IsChecked();
            }
        }
    }

    ShowNotification(TEXT("Manual settings applied!"), 2.0f);
}

// ============================================
// RESET TO DEFAULT
// ============================================
void UAtmosphereEditorWidget::ResetToDefault()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ResetToDefault() called!"));

    SetInputText(SunIntensityInput, 10.0f);
    SetInputText(SunTemperatureInput, 5500.0f);
    SetInputText(SunPitchInput, -45.0f);
    SetInputText(FogDensityInput, 0.02f);
    SetInputText(FogHeightFalloffInput, 0.2f);
    SetInputText(FogMaxOpacityInput, 1.0f);
    SetInputText(FogStartDistanceInput, 0.0f);
    SetInputText(SkyIntensityInput, 1.0f);
    SetInputText(ExposureBiasInput, 0.0f);
    SetInputText(SaturationInput, 1.0f);
    SetInputText(ContrastInput, 1.0f);
    SetCheckBoxChecked(VolumetricFogCheckbox, false);
    SetCheckBoxChecked(UnboundCheckBox, true);

    UAtmosphereToolkit::ResetToDefault();
    ShowNotification(TEXT("Reset to default!"), 2.0f);
}

// ============================================
// LOAD PRESET TABLE
// ============================================
void UAtmosphereEditorWidget::LoadPresetTable()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] LoadPresetTable() called!"));
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));

    PresetTable = LoadObject<UDataTable>(nullptr,
        TEXT("/Atmosphere_OptimizeToolkit/DT_Presets.DT_Presets"));

    if (PresetTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ PresetTable loaded successfully!"));

        TArray<FName> RowNames = PresetTable->GetRowNames();
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Found %d rows in DataTable:"), RowNames.Num());

        for (const FName& Name : RowNames)
        {
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit]   - RowName: '%s'"), *Name.ToString());
        }

        // Проверяем, есть ли Swamp
        if (PresetTable->FindRow<FAtmospherePresetData>(FName("Swamp"), TEXT("")))
        {
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ 'Swamp' row exists!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ 'Swamp' row NOT found!"));
        }

        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ PresetTable is NULL! Check path."));
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] Path: /Game/Atmosphere_OptimizeToolkit/DT_Presets.DT_Presets"));
    }
}

// ============================================
// APPLY PRESET BY NAME
// ============================================
void UAtmosphereEditorWidget::ApplyPresetByName(FName PresetName)
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ApplyPresetByName() called: '%s'"), *PresetName.ToString());
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));

    if (!PresetTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] PresetTable is NULL, loading..."));
        LoadPresetTable();
        if (!PresetTable)
        {
            UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ PresetTable is STILL NULL!"));
            ShowNotification(TEXT("Preset table not loaded!"), 2.0f);
            return;
        }
    }

    FAtmospherePresetData* Row = PresetTable->FindRow<FAtmospherePresetData>(PresetName, TEXT(""));
    if (Row)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Preset found: '%s'"), *PresetName.ToString());

        // Применяем
        UAtmosphereToolkit::ApplyPresetData(*Row);

        // Обновляем UI
        SetInputText(SunIntensityInput, Row->SunIntensity);
        SetInputText(SunTemperatureInput, Row->SunTemperature);
        SetInputText(SunPitchInput, Row->SunRotation.Pitch);
        SetInputText(FogDensityInput, Row->FogDensity);
        SetInputText(FogHeightFalloffInput, Row->FogHeightFalloff);
        SetInputText(FogMaxOpacityInput, Row->FogMaxOpacity);
        SetInputText(FogStartDistanceInput, Row->FogStartDistance);
        SetInputText(SkyIntensityInput, Row->SkyLightIntensity);
        SetInputText(ExposureBiasInput, Row->ExposureBias);
        SetInputText(SaturationInput, Row->Saturation);
        SetInputText(ContrastInput, Row->Contrast);
        SetCheckBoxChecked(VolumetricFogCheckbox, Row->bEnableVolumetricFog);

        ShowNotification(FString::Printf(TEXT("✅ Preset '%s' applied!"), *PresetName.ToString()), 2.0f);
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ✅ Preset '%s' applied successfully!"), *PresetName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[AtmosphereToolkit] ❌ Preset NOT found: '%s'"), *PresetName.ToString());

        // Выводим все доступные RowNames
        TArray<FName> RowNames = PresetTable->GetRowNames();
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Available RowNames:"));
        for (const FName& Name : RowNames)
        {
            UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit]   - '%s'"), *Name.ToString());
        }

        ShowNotification(FString::Printf(TEXT("❌ Preset '%s' not found!"), *PresetName.ToString()), 2.0f);
    }

    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] ========================================"));
}

// ============================================
// BUTTON CALLBACKS
// ============================================
void UAtmosphereEditorWidget::OnApplyManualClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnApplyManualClicked() called!"));
    ApplyManualSettings();
}

void UAtmosphereEditorWidget::OnResetDefaultClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnResetDefaultClicked() called!"));
    ResetToDefault();
}

void UAtmosphereEditorWidget::OnPreset1Clicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnPreset1Clicked() called!"));
    ApplyPresetByName(FName("Swamp"));
}

void UAtmosphereEditorWidget::OnPreset2Clicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnPreset2Clicked() called!"));
    ApplyPresetByName(FName("Forest"));
}

void UAtmosphereEditorWidget::OnPreset3Clicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnPreset3Clicked() called!"));
    ApplyPresetByName(FName("Urban"));
}

void UAtmosphereEditorWidget::OnPreset4Clicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnPreset4Clicked() called!"));
    ApplyPresetByName(FName("Night"));
}

void UAtmosphereEditorWidget::OnPreset5Clicked()
{
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] OnPreset5Clicked() called!"));
    ApplyPresetByName(FName("Sunset"));
}

// ============================================
// HELPERS
// ============================================
float UAtmosphereEditorWidget::GetFloatFromInput(UEditableText* Input, float DefaultValue)
{
    if (!Input) return DefaultValue;
    FString Text = Input->GetText().ToString().TrimStartAndEnd();
    if (Text.IsEmpty()) return DefaultValue;
    return FCString::Atof(*Text);
}

void UAtmosphereEditorWidget::SetInputText(UEditableText* Input, float Value)
{
    if (Input)
    {
        Input->SetText(FText::FromString(FString::SanitizeFloat(Value)));
    }
}

void UAtmosphereEditorWidget::SetCheckBoxChecked(UCheckBox* CheckBox, bool bChecked)
{
    if (CheckBox)
    {
        CheckBox->SetIsChecked(bChecked);
    }
}

void UAtmosphereEditorWidget::ShowNotification(const FString& Message, float Duration)
{
    FNotificationInfo Info(FText::FromString(Message));
    Info.ExpireDuration = Duration;
    FSlateNotificationManager::Get().AddNotification(Info);
}