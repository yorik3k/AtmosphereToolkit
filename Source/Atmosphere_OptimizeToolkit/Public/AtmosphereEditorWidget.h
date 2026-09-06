#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "AtmosphereToolkit.h"
#include "AtmosphereEditorWidget.generated.h"

UCLASS()
class ATMOSPHERE_OPTIMIZETOOLKIT_API UAtmosphereEditorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // ============================================
    // BIND WIDGETS (имена из WBP)
    // ============================================

    // Sun
    UPROPERTY(meta = (BindWidget))
    UEditableText* SunIntensityInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* SunTemperatureInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* SunPitchInput;

    // Fog
    UPROPERTY(meta = (BindWidget))
    UEditableText* FogDensityInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* FogHeightFalloffInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* FogMaxOpacityInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* FogStartDistanceInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* FogColorRGBInput;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* VolumetricFogCheckbox;

    // Sky
    UPROPERTY(meta = (BindWidget))
    UEditableText* SkyIntensityInput;

    // PPV
    UPROPERTY(meta = (BindWidget))
    UEditableText* ExposureBiasInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* SaturationInput;

    UPROPERTY(meta = (BindWidget))
    UEditableText* ContrastInput;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* UnboundCheckBox;

    // Buttons
    UPROPERTY(meta = (BindWidget))
    UButton* Button_ApplyManual;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetDefaultButton;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Apply_1;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Apply_2;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Apply_3;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Apply;      

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Apply_4;

    // ============================================
    // FUNCTIONS
    // ============================================

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    void LoadCurrentSettings();

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    void ApplyManualSettings();

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    void ResetToDefault();

    UFUNCTION(BlueprintCallable, Category = "Atmosphere Toolkit")
    void ApplyPresetByName(FName PresetName);

private:
    float GetFloatFromInput(UEditableText* Input, float DefaultValue = 0.0f);
    void SetInputText(UEditableText* Input, float Value);
    void SetCheckBoxChecked(UCheckBox* CheckBox, bool bChecked);
    

    FLinearColor GetColorFromInput(UEditableText* Input, FLinearColor DefaultColor = FLinearColor::White);
    void SetColorInput(UEditableText* Input, FLinearColor Color);

    void ShowNotification(const FString& Message, float Duration = 2.0f);

    UFUNCTION()
    void OnApplyManualClicked();

    UFUNCTION()
    void OnResetDefaultClicked();

    UFUNCTION()
    void OnPreset1Clicked();

    UFUNCTION()
    void OnPreset2Clicked();

    UFUNCTION()
    void OnPreset3Clicked();

    UFUNCTION()
    void OnPreset4Clicked();

    UFUNCTION()
    void OnPreset5Clicked();

    UPROPERTY()
    UDataTable* PresetTable;

    void LoadPresetTable();
};