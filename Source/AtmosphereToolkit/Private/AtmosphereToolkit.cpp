// Includes
#include "AtmosphereToolkit.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Engine/SkyLight.h"
#include "Engine/DataTable.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyLightComponent.h"
#include "EngineUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "ToolMenus.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Input/SCheckBox.h"
#include "Engine/PostProcessVolume.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Engine/Texture2D.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
//

// ============================================
// Применить настройки из DataAsset к уровню
// ============================================
void UAtmospherePreset::ApplyToCurrentLevel()
{
    FAtmospherePresetData Data;
    Data.SunIntensity = SunIntensity;
    Data.SunTemperature = SunTemperature;
    Data.SunRotation = SunRotation;
    Data.FogDensity = FogDensity;
    Data.FogColor = FogColor;
    Data.FogMaxOpacity = FogMaxOpacity;
    Data.FogStartDistance = FogStartDistance;
    Data.bEnableVolumetricFog = bEnableVolumetricFog;
    Data.FogHeightFalloff = FogHeightFalloff;
    Data.SkyLightIntensity = SkyLightIntensity;
    Data.ExposureBias = ExposureBias;
    Data.Saturation = Saturation;
    Data.Contrast = Contrast;
    ApplyPresetData(Data);
}

// ============================================
// Статическая функция — применить структуру к уровню
// ============================================
void UAtmospherePreset::ApplyPresetData(const FAtmospherePresetData& Data)
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return;
    //Dir Light
    for (TActorIterator<ADirectionalLight> It(World); It; ++It)
    {
        ADirectionalLight* Sun = *It;
        if (Sun && Sun->GetLightComponent())
        {
            Sun->GetLightComponent()->SetIntensity(Data.SunIntensity);
            Sun->GetLightComponent()->SetLightColor(FLinearColor::MakeFromColorTemperature(Data.SunTemperature));
            Sun->SetActorRotation(Data.SunRotation);
        }
    }
    // Fog
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
        }
    }

    for (TActorIterator<ASkyLight> It(World); It; ++It)
    {
        ASkyLight* Sky = *It;
        if (Sky && Sky->GetLightComponent())
        {
            Sky->GetLightComponent()->SetIntensity(Data.SkyLightIntensity);
        }
    }
    // Post Process Volume
    if (World->PostProcessVolumes.Num() > 0)
    {
        FPostProcessVolumeProperties Props = World->PostProcessVolumes[0]->GetProperties();
        FPostProcessSettings* Settings = (FPostProcessSettings*)Props.Settings;

        Settings->bOverride_AutoExposureBias = true;
        Settings->AutoExposureBias = Data.ExposureBias;

        Settings->bOverride_ColorSaturation = true;
        FVector4& Sat = Settings->ColorSaturation;
        Sat.X = Data.Saturation;
        Sat.Y = Data.Saturation;
        Sat.Z = Data.Saturation;
        Sat.W = 1.0f;

        Settings->bOverride_ColorContrast = true;
        FVector4& Con = Settings->ColorContrast;
        Con.X = Data.Contrast;
        Con.Y = Data.Contrast;
        Con.Z = Data.Contrast;
        Con.W = 1.0f;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] PostProcessVolume not found. Add one to apply post-process settings."));
    }

    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Manual settings applied. Sun=%.1f, Fog=%.3f, Sky=%.1f"),
        Data.SunIntensity, Data.FogDensity, Data.SkyLightIntensity);
}

// ============================================
// Получить список пресетов из DataTable
// ============================================
TArray<FName> UAtmospherePreset::GetPresetRowNames()
{
    TArray<FName> Names;
    UDataTable* PresetTable = LoadObject<UDataTable>(nullptr,
        TEXT("/Game/AtmosphereToolkit/DT_Presets.DT_Presets"));
    if (PresetTable)
    {
        Names = PresetTable->GetRowNames();
    }
    return Names;
}

// ============================================
// Создать DataTable с пресетами
// ============================================
void CreatePresetDataTable()
{
    FString Path = TEXT("/Game/AtmosphereToolkit/");
    FString Name = TEXT("DT_Presets");

    UDataTable* Existing = LoadObject<UDataTable>(nullptr, *(Path + Name + TEXT(".") + Name));
    if (Existing)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] DataTable уже существует."));
        return;
    }

    UPackage* Pkg = CreatePackage(*(Path + Name));
    if (!Pkg) return;

    UDataTable* Table = NewObject<UDataTable>(Pkg, *Name, RF_Public | RF_Standalone);
    if (!Table) return;

    Table->RowStruct = FAtmospherePresetData::StaticStruct();

    auto Add = [&](const TCHAR* RowName, const TCHAR* Label,
        float SunI, float SunT, float Pitch,
        float FogD, float FogR, float FogG, float FogB,
        float FogMaxOp, float FogHeightF, float FogStartDist, bool EnableVolFog,
        float ExpBias, float Sat, float Con, float SkyI)
        {
            FAtmospherePresetData D;
            D.PresetName = FText::FromString(Label);
            D.SunIntensity = SunI;
            D.SunTemperature = SunT;
            D.SunRotation = FRotator(Pitch, 0.0f, 0.0f);
            D.FogDensity = FogD;
            D.FogColor = FLinearColor(FogR, FogG, FogB);
            D.FogMaxOpacity = FogMaxOp;
            D.FogHeightFalloff = FogHeightF;
            D.FogStartDistance = FogStartDist;
            D.bEnableVolumetricFog = EnableVolFog;

            D.ExposureBias = ExpBias;
            D.Saturation = Sat;
            D.Contrast = Con;
            D.SkyLightIntensity = SkyI;
            Table->AddRow(FName(RowName), D);
        };
    ///
    /// PRESSETS TABLE
    /// 
    
    //Swamp  ExpB Sat  Con
    Add(TEXT("Swamp"), TEXT("Swamp"), 5.0f, 4500.0f, -60.0f, 0.15f, 0.3f, 0.5f, 0.2f, 1.0f, 0.2f, 0.0f, true, -0.5f, 0.8f, 1.1f, 0.5f);

    //Urban
    Add(TEXT("Urban"), TEXT("Urban"), 12.0f, 6500.0f, -30.0f, 0.02f, 0.6f, 0.6f, 0.7f, 1.0f, 0.3f, 0.0f, false, 0.0f, 1.0f, 1.0f, 1.5f);

    //Forest
    Add(TEXT("Forest"), TEXT("Forest"), 3.0f, 4000.0f, -75.0f, 0.08f, 0.2f, 0.4f, 0.15f, 1.0f, 0.1f, 0.0f, true, -1.0f, 0.6f, 1.2f, 0.3f);

    //Night
    Add(TEXT("Night"), TEXT("Night"), 0.5f, 3000.0f, -90.0f, 0.04f, 0.1f, 0.1f, 0.3f, 1.0f, 0.5f, 0.0f, false, -2.0f, 0.4f, 0.8f, 0.1f);

    //Sunset
    Add(TEXT("Sunset"), TEXT("Sunset"), 8.0f, 2500.0f, -10.0f, 0.05f, 1.0f, 0.5f, 0.2f, 1.0f, 0.2f, 0.0f, false, 0.5f, 1.3f, 1.1f, 0.8f);

    Pkg->MarkPackageDirty();
    FString FilePath = FPackageName::LongPackageNameToFilename(Path + Name, FPackageName::GetAssetPackageExtension());
    FSavePackageArgs SaveArgs;
    SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
    UPackage::SavePackage(Pkg, Table, *FilePath, SaveArgs);

    FAssetRegistryModule::AssetCreated(Table);
    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] DataTable DT_Presets создан!"));
}

// ============================================
// Модуль
// ============================================
void FAtmosphereToolkitModule::StartupModule()
{
    UToolMenus::Get()->RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateLambda([]()
            {
                UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");

                ///
                /// Static Scene Optimizer (in-dev on 16-07-2026)
                /// 
                FToolMenuSection& OptimizerSection = Menu->AddSection("SceneOptimizer",
                    FText::FromString("Scene Optimizer"));

                OptimizerSection.AddMenuEntry(
                    "OptimizerWindow",
                    TAttribute<FText>(FText::FromString("Static Scene Optimizer")),
                    TAttribute<FText>(FText::FromString("Open scene optimization tools")),
                    FSlateIcon(),
                    FToolUIActionChoice(FUIAction(
                        FExecuteAction::CreateLambda([]()
                            {
                                TSharedRef<SWindow> OptWindow = SNew(SWindow)
                                    .Title(FText::FromString("Static Scene Optimizer"))
                                    .ClientSize(FVector2D(500, 400))
                                    .SizingRule(ESizingRule::UserSized);

                                TSharedRef<SVerticalBox> OptContent = SNew(SVerticalBox);

                                // Заголовок
                                OptContent->AddSlot().AutoHeight().Padding(20)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Static Scene Optimizer"))
                                            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
                                    ];

                                // Описание
                                OptContent->AddSlot().AutoHeight().Padding(20, 0)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("This module automates optimization of static meshes:\n- Auto Cull Distance by mesh size\n- Grouping by material\n- Convert to Instanced Static Meshes\n\nSelect meshes in the viewport and click Optimize."))
                                            .AutoWrapText(true)
                                    ];

                                // Разделитель
                                OptContent->AddSlot().AutoHeight().Padding(20, 10)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Status: Under Development"))
                                            .ColorAndOpacity(FLinearColor(1.0f, 0.8f, 0.2f))
                                    ];

                                // Кнопка-заглушка
                                OptContent->AddSlot().AutoHeight().Padding(20, 0)
                                    [
                                        SNew(SButton)
                                            .Text(FText::FromString("Auto Cull Distance (WIP)"))
                                            .OnClicked_Lambda([]()
                                                {
                                                    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Auto Cull Distance - coming soon. :)"));
                                                    return FReply::Handled();
                                                })
                                    ];

                                OptContent->AddSlot().AutoHeight().Padding(10, 0)
                                    [
                                        SNew(SButton)
                                            .Text(FText::FromString("Convert to ISM (WIP)"))
                                            .OnClicked_Lambda([]()
                                                {
                                                    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Convert to ISM - coming soon. :)"));
                                                    return FReply::Handled();
                                                })
                                    ];

                                OptContent->AddSlot().AutoHeight().Padding(10, 0)
                                    [
                                        SNew(SButton)
                                            .Text(FText::FromString("Merge Selected Meshes (WIP)"))
                                            .OnClicked_Lambda([]()
                                                {
                                                    UE_LOG(LogTemp, Warning, TEXT("[AtmosphereToolkit] Merge Meshes - coming soon. :)"));
                                                    return FReply::Handled();
                                                })
                                    ];

                                OptWindow->SetContent(OptContent);
                                FSlateApplication::Get().AddWindow(OptWindow);
                            })
                    ))
                );

                FToolMenuSection& Section = Menu->AddSection("AtmospherePresets",
                    FText::FromString("Level-design tooltit"));

                Section.AddMenuEntry(
                    "PresetWindow",
                    TAttribute<FText>(FText::FromString("Atmosphere Presets")),
                    TAttribute<FText>(FText::FromString("Open atmosphere presets window")),
                    FSlateIcon(),
                    FToolUIActionChoice(FUIAction(
                        FExecuteAction::CreateLambda([]()
                            {
                                TSharedRef<SWindow> PresetWindow = SNew(SWindow)
                                    .Title(FText::FromString("Atmosphere Presets"))
                                    .ClientSize(FVector2D(700, 500))
                                    .SizingRule(ESizingRule::UserSized);

                                TSharedRef<SScrollBox> PresetScroll = SNew(SScrollBox);
                                TSharedRef<SVerticalBox> PresetContent = SNew(SVerticalBox);

                                PresetScroll->AddSlot()
                                    [
                                        PresetContent
                                    ];

                                // Заголовок
                                PresetContent->AddSlot().AutoHeight().Padding(10)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Quick Presets"))
                                            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
                                    ];

                                // Описание
                                PresetContent->AddSlot().AutoHeight().Padding(10, 0, 10, 10)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Click a preset to apply it to the current level."))
                                            .AutoWrapText(true)
                                    ];

                                // Плитки пресетов (3 в ряд)
                                auto AddPresetTile = [&](FName RowName, const FString& Description)
                                    {
                                        // Создаём строку каждые 3 пресета
                                        static int32 TileCount = 0;
                                        if (TileCount % 3 == 0)
                                        {
                                            PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                                [
                                                    SNew(SHorizontalBox)
                                                ];
                                        }

                                        // Находим текущую строку (последний HorizontalBox)
                                        // Упрощаем — кладём по одному в строку, работает
                                        PresetContent->AddSlot().AutoHeight().Padding(5)
                                            [
                                                SNew(SBorder)
                                                    .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
                                                    .Padding(10)
                                                    [
                                                        SNew(SVerticalBox)
                                                            // Изображение пресета
                                                            + SVerticalBox::Slot().AutoHeight()
                                                            [
                                                                SNew(SBox).WidthOverride(250).HeightOverride(150)
                                                                    [
                                                                        ([RowName]() -> TSharedRef<SWidget>
                                                                            {
                                                                                FString TexturePath;
                                                                                if (RowName == FName("Swamp"))
                                                                                    TexturePath = TEXT("/Game/AtmosphereToolkit/Icons/swamp");
                                                                                else if (RowName == FName("Forest"))
                                                                                    TexturePath = TEXT("/Game/AtmosphereToolkit/Icons/forest");
                                                                                else if (RowName == FName("Urban"))
                                                                                    TexturePath = TEXT("/Game/AtmosphereToolkit/Icons/urban");

                                                                                UTexture2D* Tex = nullptr;
                                                                                if (!TexturePath.IsEmpty())
                                                                                    Tex = LoadObject<UTexture2D>(nullptr, *TexturePath);

                                                                                if (Tex)
                                                                                    return SNew(SImage).Image(new FSlateImageBrush(Tex, FVector2D(Tex->GetSizeX(), Tex->GetSizeY())));

                                                                                return SNew(SBorder)
                                                                                    .BorderImage(FAppStyle::GetBrush("WhiteBrush"))
                                                                                    .BorderBackgroundColor(FLinearColor(0.05f, 0.05f, 0.08f))
                                                                                    .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                                                                    [
                                                                                        SNew(STextBlock)
                                                                                            .Text(FText::FromString("No Preview"))
                                                                                            .ColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.4f))
                                                                                    ];
                                                                            }())
                                                                    ]
                                                            ]
                                                        // Название
                                                        + SVerticalBox::Slot().AutoHeight().Padding(0, 8, 0, 4)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromName(RowName))
                                                                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 12))
                                                                    .Justification(ETextJustify::Center)
                                                            ]
                                                            // Описание
                                                            + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 8)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString(Description))
                                                                    .AutoWrapText(true)
                                                                    .Justification(ETextJustify::Center)
                                                            ]
                                                            // Кнопка Apply
                                                            + SVerticalBox::Slot().AutoHeight()
                                                            [
                                                                SNew(SButton)
                                                                    .Text(FText::FromString("Apply"))
                                                                    .HAlign(HAlign_Center)
                                                                    .OnClicked_Lambda([RowName]()
                                                                        {
                                                                            UDataTable* DT = LoadObject<UDataTable>(nullptr,
                                                                                TEXT("/Game/AtmosphereToolkit/DT_Presets.DT_Presets"));
                                                                            if (DT)
                                                                            {
                                                                                FAtmospherePresetData* Row = DT->FindRow<FAtmospherePresetData>(RowName, TEXT(""));
                                                                                if (Row)
                                                                                {
                                                                                    UAtmospherePreset::ApplyPresetData(*Row);
                                                                                    FString Msg = TEXT("Preset '") + RowName.ToString() + TEXT("' applied!");
                                                                                    FNotificationInfo Info(FText::FromString(Msg));
                                                                                    Info.ExpireDuration = 3.0f;
                                                                                    FSlateNotificationManager::Get().AddNotification(Info);
                                                                                }
                                                                            }
                                                                            return FReply::Handled();
                                                                        })
                                                            ]
                                                    ]
                                            ];
                                        TileCount++;
                                    };

                                    // Автоматически строим плитки из DataTable
                                    UDataTable* DT = LoadObject<UDataTable>(nullptr,
                                        TEXT("/Game/AtmosphereToolkit/DT_Presets.DT_Presets"));
                                    if (DT)
                                    {
                                        TArray<FName> RowNames = DT->GetRowNames();
                                        for (const FName& RowName : RowNames)
                                        {
                                            FAtmospherePresetData* Row = DT->FindRow<FAtmospherePresetData>(RowName, TEXT(""));
                                            FString Desc = Row ? Row->PresetName.ToString() : TEXT("Custom Preset");
                                            AddPresetTile(RowName, Desc);
                                        }
                                    }

                                // Разделитель
                                PresetContent->AddSlot().AutoHeight().Padding(10, 15)
                                    [
                                        SNew(SSeparator)
                                    ];
                                // Кнопка в окне пресетов
                                PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SButton)
                                            .Text(FText::FromString("Instructions for use"))
                                            .HAlign(HAlign_Center)
                                            .OnClicked_Lambda([]()
                                                {
                                                    // Создаём окно
                                                    TSharedRef<SWindow> PressetUsingInfo = SNew(SWindow)
                                                        .Title(FText::FromString("Atmosphere Pressets: Manual"))
                                                        .ClientSize(FVector2D(500, 600))
                                                        .SizingRule(ESizingRule::UserSized);

                                                    // Контейнер с прокруткой
                                                    TSharedRef<SScrollBox> Scroll = SNew(SScrollBox);
                                                    TSharedRef<SVerticalBox> Content = SNew(SVerticalBox);
                                                    Scroll->AddSlot()[Content];

                                                    // Заголовок
                                                    Content->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("Instructions for using the Atmosphere Preset module"))
                                                                .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 14))
                                                                .ColorAndOpacity(FLinearColor(1, 0.8, 0.2))
                                                        ];

                                                    // Иконка + текст в одной строке
                                                    Content->AddSlot().AutoHeight().Padding(10, 0)
                                                        [
                                                            SNew(SHorizontalBox)
                                                                + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(0, 0, 8, 0)
                                                                [
                                                                    SNew(SImage)
                                                                        .Image(FAppStyle::GetBrush("Icons.Info"))
                                                                        .DesiredSizeOverride(FVector2D(24, 24))
                                                                ]
                                                                + SHorizontalBox::Slot().FillWidth(1.0f)
                                                                [
                                                                    SNew(STextBlock)
                                                                        .Text(FText::FromString("Welcome to the Atmosphere Presets module!\nThis is a usage guide to prevent you from doing anything\nstupid :)"))
                                                                        .AutoWrapText(true)
                                                                ]
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("- Using ready-made presets"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("- Creating your own presets"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("- Creating your own presets"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("1. Creating your own presets:"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("The module allows you to create your own presets by saving the current \nLumen settings on the stage."))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("After creating a preset, it is mandatory to save all changes at the level."))
                                                                .AutoWrapText(true)
                                                        ];
                                                    // Иконка + текст в одной строке
                                                    Content->AddSlot().AutoHeight().Padding(10, 0)
                                                        [
                                                            SNew(SHorizontalBox)
                                                                + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(0, 0, 8, 0)
                                                                [
                                                                    SNew(SImage)
                                                                        .Image(FAppStyle::GetBrush("Icons.Warning"))
                                                                        .DesiredSizeOverride(FVector2D(24, 24))
                                                                ]
                                                                + SHorizontalBox::Slot().FillWidth(1.0f)
                                                                [
                                                                    SNew(STextBlock)
                                                                        .Text(FText::FromString("Otherwise, the preset will not be saved!"))
                                                                        .AutoWrapText(true)
                                                                        .ColorAndOpacity(FLinearColor(1, 0.5, 0.0))
                                                                ]
                                                        ];
                                                    Content->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("2. Removing presets"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("The user can delete both their own presets and the preset presets."))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("To do this, click on the Remove button in the presets menu, select the preset"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("to be deleted with a checkmark, and click on delete"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    // Иконка + текст в одной строке
                                                    Content->AddSlot().AutoHeight().Padding(10, 0)
                                                        [
                                                            SNew(SHorizontalBox)
                                                                + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(0, 0, 8, 0)
                                                                [
                                                                    SNew(SImage)
                                                                        .Image(FAppStyle::GetBrush("Icons.Warning"))
                                                                        .DesiredSizeOverride(FVector2D(24, 24))
                                                                ]
                                                                + SHorizontalBox::Slot().FillWidth(1.0f)
                                                                [
                                                                    SNew(STextBlock)
                                                                        .Text(FText::FromString("Attention! Presets cannot be restored, and the plugin will NOT confirm your selection. \nUse the delete function with caution!"))
                                                                        .AutoWrapText(true)
                                                                        .ColorAndOpacity(FLinearColor(1, 0.5, 0.0))
                                                                ]
                                                        ];
                                                    Content->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("3. Using ready-made presets."))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("Ready-made presets are provided to the user for quick level adjustment."))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("Presets provided by developers are not subject to change, except for deletion by the user (see point 2)"))
                                                                .AutoWrapText(true)
                                                        ];
                                                    Content->AddSlot().AutoHeight()
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("To apply a preset, you need to click on the [Apply] button in the corresponding block."))
                                                                .AutoWrapText(true)
                                                        ];
                                                    // Иконка + текст в одной строке
                                                    Content->AddSlot().AutoHeight().Padding(10, 0)
                                                        [
                                                            SNew(SHorizontalBox)
                                                                + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(0, 0, 8, 0)
                                                                [
                                                                    SNew(SImage)
                                                                        .Image(FAppStyle::GetBrush("Icons.Info"))
                                                                        .DesiredSizeOverride(FVector2D(24, 24))
                                                                ]
                                                                + SHorizontalBox::Slot().FillWidth(1.0f)
                                                                [
                                                                    SNew(STextBlock)
                                                                        .Text(FText::FromString("All changes made using the plugin must be saved! Use Ctrl + S to save all changes at the level."))
                                                                        .AutoWrapText(true)
                                                                        .ColorAndOpacity(FLinearColor(0.2, 0.6, 1))
                                                                ]
                                                        ];

                                                    

                                                    PressetUsingInfo->SetContent(Scroll);
                                                    FSlateApplication::Get().AddWindow(PressetUsingInfo);
                                                    return FReply::Handled();
                                                })
                                    ];

                                // Разделитель
                                PresetContent->AddSlot().AutoHeight().Padding(10, 15)
                                    [
                                        SNew(SSeparator)
                                    ];
                                // Кнопка сброса
                                PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SButton)
                                            .Text(FText::FromString("Reset to Default"))
                                            .HAlign(HAlign_Center)
                                            .OnClicked_Lambda([]()
                                                {
                                                    FAtmospherePresetData Data;
                                                    Data.SunIntensity = 10.0f;
                                                    Data.SunTemperature = 5500.0f;
                                                    Data.SunRotation = FRotator(-45.0f, 0.0f, 0.0f);
                                                    Data.FogDensity = 0.02f;
                                                    Data.FogMaxOpacity = 1.0f;
                                                    Data.FogHeightFalloff = 0.2f;
                                                    Data.FogStartDistance = 0.0f;
                                                    Data.bEnableVolumetricFog = false;
                                                    Data.FogColor = FLinearColor(0.5f, 0.6f, 0.8f);
                                                    Data.SkyLightIntensity = 1.0f;
                                                    Data.ExposureBias = 0.0f;
                                                    Data.Saturation = 1.0f;
                                                    Data.Contrast = 1.0f;
                                                    UAtmospherePreset::ApplyPresetData(Data);

                                                    FNotificationInfo Info(FText::FromString("Manual settings applied!"));
                                                    Info.ExpireDuration = 3.0f;
                                                    FSlateNotificationManager::Get().AddNotification(Info);

                                                    return FReply::Handled();
                                                })
                                    ];
                                // Разделитель
                                PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SSeparator)
                                    ];

                                PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SButton)
                                            .Text(FText::FromString("Save Current as Preset"))
                                            .HAlign(HAlign_Center)
                                            .OnClicked_Lambda([PresetWindow]()
                                                {
                                                    // Маленькое окно для ввода имени
                                                    TSharedRef<SWindow> NameWindow = SNew(SWindow)
                                                        .Title(FText::FromString("Save Preset"))
                                                        .ClientSize(FVector2D(300, 120))
                                                        .SizingRule(ESizingRule::UserSized);

                                                    TSharedPtr<SEditableTextBox> NameBox;
                                                    TSharedPtr<SEditableTextBox> DescBox;

                                                    TSharedRef<SVerticalBox> NameContent = SNew(SVerticalBox);
                                                    NameContent->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(STextBlock).Text(FText::FromString("Preset name:"))
                                                        ];
                                                    NameContent->AddSlot().AutoHeight().Padding(10, 0)
                                                        [
                                                            SAssignNew(NameBox, SEditableTextBox).Text(FText::FromString("My Preset"))
                                                        ];
                                                    NameContent->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(STextBlock).Text(FText::FromString("Description:"))
                                                        ];
                                                    NameContent->AddSlot().AutoHeight().Padding(10, 0)
                                                        [
                                                            SAssignNew(DescBox, SEditableTextBox).Text(FText::FromString("Custom preset"))
                                                        ];
                                                    NameContent->AddSlot().AutoHeight().Padding(10)
                                                        [
                                                            SNew(SButton)
                                                                .Text(FText::FromString("Save"))
                                                                .OnClicked_Lambda([NameBox, DescBox, NameWindow]()
                                                                    {
                                                                        FString PresetName = NameBox->GetText().ToString();
                                                                        FString Description = DescBox->GetText().ToString();

                                                                        UWorld* World = GEditor->GetEditorWorldContext().World();
                                                                        if (!World) return FReply::Handled();

                                                                        FAtmospherePresetData NewData;
                                                                        NewData.PresetName = FText::FromString(Description);

                                                                        // Читаем DirectionalLight
                                                                        for (TActorIterator<ADirectionalLight> It(World); It; ++It)
                                                                        {
                                                                            ADirectionalLight* Sun = *It;
                                                                            if (Sun && Sun->GetLightComponent())
                                                                            {
                                                                                NewData.SunIntensity = Sun->GetLightComponent()->Intensity;
                                                                                NewData.SunTemperature = Sun->GetLightComponent()->Temperature;
                                                                                NewData.SunRotation = Sun->GetActorRotation();
                                                                                break;
                                                                            }
                                                                        }

                                                                        // Читаем Fog
                                                                        for (TActorIterator<AExponentialHeightFog> It(World); It; ++It)
                                                                        {
                                                                            AExponentialHeightFog* Fog = *It;
                                                                            if (Fog && Fog->GetComponent())
                                                                            {
                                                                                NewData.FogDensity = Fog->GetComponent()->FogDensity;
                                                                                NewData.FogMaxOpacity = Fog->GetComponent()->FogMaxOpacity;
                                                                                NewData.FogHeightFalloff = Fog->GetComponent()->FogHeightFalloff;
                                                                                NewData.FogStartDistance = Fog->GetComponent()->StartDistance;
                                                                                NewData.bEnableVolumetricFog = Fog->GetComponent()->bEnableVolumetricFog;
                                                                                break;
                                                                            }
                                                                        }

                                                                        // Читаем SkyLight
                                                                        for (TActorIterator<ASkyLight> It(World); It; ++It)
                                                                        {
                                                                            ASkyLight* Sky = *It;
                                                                            if (Sky && Sky->GetLightComponent())
                                                                            {
                                                                                NewData.SkyLightIntensity = Sky->GetLightComponent()->Intensity;
                                                                                break;
                                                                            }
                                                                        }

                                                                        // Читаем PPV
                                                                        if (World->PostProcessVolumes.Num() > 0)
                                                                        {
                                                                            FPostProcessVolumeProperties Props = World->PostProcessVolumes[0]->GetProperties();
                                                                            FPostProcessSettings* Settings = (FPostProcessSettings*)Props.Settings;
                                                                            NewData.ExposureBias = Settings->AutoExposureBias;
                                                                            NewData.Saturation = Settings->ColorSaturation.X;
                                                                            NewData.Contrast = Settings->ColorContrast.X;
                                                                        }

                                                                        // Сохраняем
                                                                        UDataTable* DT = LoadObject<UDataTable>(nullptr,
                                                                            TEXT("/Game/AtmosphereToolkit/DT_Presets.DT_Presets"));
                                                                        if (DT)
                                                                        {
                                                                            FName NewRowName = FName(*PresetName);
                                                                            DT->AddRow(NewRowName, NewData);
                                                                            DT->MarkPackageDirty();

                                                                            FNotificationInfo Info(FText::FromString("Preset saved! Reopen window."));
                                                                            Info.ExpireDuration = 3.0f;
                                                                            FSlateNotificationManager::Get().AddNotification(Info);
                                                                        }

                                                                        NameWindow->RequestDestroyWindow();
                                                                        return FReply::Handled();
                                                                    })

                                                        ];


                                                    NameWindow->SetContent(NameContent);
                                                    FSlateApplication::Get().AddWindow(NameWindow);
                                                    return FReply::Handled();
                                                })
                                    ];
                                    // Кнопка удаления
                                    PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                        [
                                            SNew(SButton)
                                                .HAlign(HAlign_Center)
                                                .OnClicked_Lambda([]()
                                                    {
                                                        TSharedRef<SWindow> DelWindow = SNew(SWindow)
                                                            .Title(FText::FromString("Delete Presets"))
                                                            .ClientSize(FVector2D(350, 400))
                                                            .SizingRule(ESizingRule::UserSized);

                                                        TSharedRef<SScrollBox> DelScroll = SNew(SScrollBox);
                                                        TSharedRef<SVerticalBox> DelContent = SNew(SVerticalBox);

                                                        DelScroll->AddSlot()[DelContent];

                                                        UDataTable* DT = LoadObject<UDataTable>(nullptr,
                                                            TEXT("/Game/AtmosphereToolkit/DT_Presets.DT_Presets"));

                                                        TArray<TSharedPtr<SCheckBox>> CheckBoxes;
                                                        TArray<FName> RowNames;

                                                        if (DT)
                                                        {
                                                            RowNames = DT->GetRowNames();
                                                            for (const FName& Name : RowNames)
                                                            {
                                                                TSharedPtr<SCheckBox> CheckBox;
                                                                DelContent->AddSlot().AutoHeight().Padding(5)
                                                                    [
                                                                        SNew(SHorizontalBox)
                                                                            + SHorizontalBox::Slot().AutoWidth()
                                                                            [
                                                                                SAssignNew(CheckBox, SCheckBox)
                                                                            ]
                                                                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(5, 0, 0, 0)
                                                                            [
                                                                                SNew(STextBlock).Text(FText::FromName(Name))
                                                                            ]
                                                                    ];
                                                                CheckBoxes.Add(CheckBox);
                                                            }
                                                        }

                                                        DelContent->AddSlot().AutoHeight().Padding(10)
                                                            [
                                                                SNew(SButton)
                                                                    .OnClicked_Lambda([DT, RowNames, CheckBoxes, DelWindow]()
                                                                        {
                                                                            if (!DT) return FReply::Handled();

                                                                            for (int32 i = 0; i < RowNames.Num(); ++i)
                                                                            {
                                                                                if (CheckBoxes[i]->IsChecked())
                                                                                {
                                                                                    DT->RemoveRow(RowNames[i]);
                                                                                }
                                                                            }
                                                                            DT->MarkPackageDirty();

                                                                            FNotificationInfo Info(FText::FromString("Presets deleted. Reopen window."));
                                                                            Info.ExpireDuration = 3.0f;
                                                                            FSlateNotificationManager::Get().AddNotification(Info);

                                                                            DelWindow->RequestDestroyWindow();
                                                                            return FReply::Handled();
                                                                        })
                                                                    [
                                                                        SNew(SHorizontalBox)
                                                                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 5, 0)
                                                                            [
                                                                                SNew(SImage)
                                                                                    .Image(FAppStyle::GetBrush("Icons.Delete"))
                                                                                    .DesiredSizeOverride(FVector2D(16, 16))
                                                                            ]
                                                                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                                                                            [
                                                                                SNew(STextBlock)
                                                                                    .Text(FText::FromString("Delete Selected"))
                                                                            ]
                                                                    ]
                                                            ];

                                                        DelWindow->SetContent(DelScroll);
                                                        FSlateApplication::Get().AddWindow(DelWindow);
                                                        return FReply::Handled();
                                                    })
                                                [
                                                    SNew(SHorizontalBox)
                                                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 5, 0)
                                                        [
                                                            SNew(SImage)
                                                                .Image(FAppStyle::GetBrush("Icons.Delete"))
                                                                .DesiredSizeOverride(FVector2D(16, 16))
                                                        ]
                                                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                                                        [
                                                            SNew(STextBlock)
                                                                .Text(FText::FromString("Delete Presets"))
                                                        ]
                                                ]
                                        ];
                                    // Разделитель
                                    PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                        [
                                            SNew(SSeparator)
                                        ];
                                    // Кнопка "About"
                                    PresetContent->AddSlot().AutoHeight().Padding(10, 5)
                                        [
                                            SNew(SButton)
                                                .Text(FText::FromString("About the Developer"))
                                                .HAlign(HAlign_Center)
                                                .OnClicked_Lambda([]()
                                                    {
                                                        TSharedRef<SWindow> AboutWindow = SNew(SWindow)
                                                            .Title(FText::FromString("About"))
                                                            .ClientSize(FVector2D(350, 250))
                                                            .SizingRule(ESizingRule::UserSized);

                                                        TSharedRef<SVerticalBox> AboutContent = SNew(SVerticalBox);

                                                        AboutContent->AddSlot().AutoHeight().Padding(10)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString("Atmosphere Toolkit"))
                                                                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 14))
                                                            ];

                                                        AboutContent->AddSlot().AutoHeight().Padding(10, 0)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString("Developed by @yorik3k"))
                                                                    .AutoWrapText(true)
                                                            ];

                                                        AboutContent->AddSlot().AutoHeight().Padding(10, 5)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString("Links:"))
                                                                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
                                                            ];

                                                        // Кнопка-ссылка (открывает URL в браузере)
                                                        AboutContent->AddSlot().AutoHeight().Padding(10, 2)
                                                            [
                                                                SNew(SButton)
                                                                    .Text(FText::FromString("GitHub"))
                                                                    .OnClicked_Lambda([]()
                                                                        {
                                                                            FPlatformProcess::LaunchURL(TEXT("https://github.com/yorik3k"), nullptr, nullptr);
                                                                            return FReply::Handled();
                                                                        })
                                                            ];

                                                        

                                                        AboutWindow->SetContent(AboutContent);
                                                        FSlateApplication::Get().AddWindow(AboutWindow);
                                                        return FReply::Handled();
                                                    })
                                        ];

                                PresetWindow->SetContent(PresetScroll);
                                FSlateApplication::Get().AddWindow(PresetWindow);
                            })
                    ))
                );
                                
                FToolMenuSection& ManualSection = Menu->AddSection("ManualSettings",
                    FText::FromString("Manual-mode"));

                // --- Ручная настройка ---
                ManualSection.AddMenuEntry(
                    "ManualEdit",
                    TAttribute<FText>(FText::FromString("Manual Atmosphere Editor")),
                    TAttribute<FText>(FText::FromString("Open manual atmosphere editor window")),
                    FSlateIcon(),
                    FToolUIActionChoice(FUIAction(
                        FExecuteAction::CreateLambda([]()
                            {
                                TSharedPtr<SEditableTextBox> SunIntensityBox;
                                TSharedPtr<SEditableTextBox> SunTempBox;
                                TSharedPtr<SEditableTextBox> SunPitchBox;
                                TSharedPtr<SEditableTextBox> FogDensityBox;
                                TSharedPtr<SEditableTextBox> FogHeightFalloffBox;
                                TSharedPtr<SEditableTextBox> FogMaxOpacityBox;
                                TSharedPtr<SEditableTextBox> FogStartDistanceBox;
                                TSharedPtr<SCheckBox> VolumetricFogCheckBox;
                                TSharedPtr<SEditableTextBox> SkyIntensityBox;
                                TSharedPtr<SEditableTextBox> ExposureBiasBox;
                                TSharedPtr<SEditableTextBox> SaturationBox;
                                TSharedPtr<SEditableTextBox> ContrastBox;

                                TSharedRef<SWindow> Window = SNew(SWindow)
                                    .Title(FText::FromString("Atmosphere Manual Editor"))
                                    .ClientSize(FVector2D(400, 500))
                                    .SizingRule(ESizingRule::UserSized);

                                TSharedRef<SScrollBox> ScrollContent = SNew(SScrollBox);
                                TSharedRef<SVerticalBox> Content = SNew(SVerticalBox);

                                ScrollContent->AddSlot()
                                    [
                                        Content
                                    ];

                                // === ЗАГОЛОВОК ===
                                Content->AddSlot().AutoHeight().Padding(10)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Manual Atmosphere Setup"))
                                            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 14))
                                    ];

                                // === ОПИСАНИЕ ===
                                Content->AddSlot().AutoHeight().Padding(10, 0, 10, 5)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Adjust atmosphere parameters manually. All changes apply to the current level immediately."))
                                            .AutoWrapText(true)
                                    ];

                                // === ПРЕДУПРЕЖДЕНИЕ PPV ===
                                Content->AddSlot().AutoHeight().Padding(10, 0, 10, 10)
                                    [
                                        SNew(SHorizontalBox)
                                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 8, 0)
                                            [
                                                SNew(SImage)
                                                    .Image(FAppStyle::GetBrush("Icons.Warning"))
                                                    .DesiredSizeOverride(FVector2D(32, 32))
                                            ]
                                            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
                                            [
                                                SNew(STextBlock)
                                                    .Text(FText::FromString("Add DirectionalLight, SkyLight, ExponentialHeightFog and PostProcessVolume to the level before using manual settings."))
                                                    .ColorAndOpacity(FLinearColor(1.0f, 0.8f, 0.2f))
                                                    .AutoWrapText(true)
                                            ]
                                    ];

                                // ============================================
                                // DIRECTIONAL LIGHT (рамка)
                                // ============================================
                                Content->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SBorder)
                                            .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
                                            .Padding(10)
                                            [
                                                SNew(SVerticalBox)

                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 5, 0)
                                                            [
                                                                SNew(SImage)
                                                                    .Image(FAppStyle::GetBrush("ClassIcon.DirectionalLight"))
                                                                    .DesiredSizeOverride(FVector2D(16, 16))
                                                            ]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString("Directional Light"))
                                                                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
                                                            ]
                                                    ]
                                                // Intensity
                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Intensity: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(SunIntensityBox, SEditableTextBox).Text(FText::FromString("10.0"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Temperature: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(SunTempBox, SEditableTextBox).Text(FText::FromString("5500.0"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Pitch: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(SunPitchBox, SEditableTextBox).Text(FText::FromString("-45.0"))]
                                                    ]
                                            ]
                                    ];

                                // ============================================
                                // FOG (рамка)
                                // ============================================
                                Content->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SBorder)
                                            .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
                                            .Padding(10)
                                            [
                                                SNew(SVerticalBox)
                                                    
                                                        +SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)
                                                            [
                                                                SNew(SHorizontalBox)
                                                                    + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 5, 0)
                                                                    [
                                                                        SNew(SImage)
                                                                            .Image(FAppStyle::GetBrush("ClassIcon.ExponentialHeightFog"))
                                                                            .DesiredSizeOverride(FVector2D(16, 16))
                                                                    ]
                                                                    + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
                                                                    [
                                                                        SNew(STextBlock)
                                                                            .Text(FText::FromString("Fog"))
                                                                            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
                                                                    ]
                                                            ]
                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Density: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(FogDensityBox, SEditableTextBox).Text(FText::FromString("0.02"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Height Falloff: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(FogHeightFalloffBox, SEditableTextBox).Text(FText::FromString("0.2"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Max Opacity: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(FogMaxOpacityBox, SEditableTextBox).Text(FText::FromString("1.0"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Start Distance: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(FogStartDistanceBox, SEditableTextBox).Text(FText::FromString("0.0"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Volumetric Fog: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(VolumetricFogCheckBox, SCheckBox).IsChecked(ECheckBoxState::Unchecked)]
                                                    ]
                                            ]
                                    ];

                                // ============================================
                                // SKY LIGHT (рамка)
                                // ============================================
                                Content->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SBorder)
                                            .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
                                            .Padding(10)
                                            [
                                                SNew(SVerticalBox)
                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 5, 0)
                                                            [
                                                                SNew(SImage)
                                                                    .Image(FAppStyle::GetBrush("ClassIcon.SkyLight"))
                                                                    .DesiredSizeOverride(FVector2D(16, 16))
                                                            ]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString("Sky Light"))
                                                                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
                                                            ]
                                                    ]
                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Intensity: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(SkyIntensityBox, SEditableTextBox).Text(FText::FromString("1.0"))]
                                                    ]
                                            ]
                                    ];

                                // ============================================
                                // POST PROCESS VOLUME (рамка)
                                // ============================================
                                Content->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(SBorder)
                                            .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
                                            .Padding(10)
                                            [
                                                SNew(SVerticalBox)
                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 5, 0)
                                                            [
                                                                SNew(SImage)
                                                                    .Image(FAppStyle::GetBrush("ClassIcon.PostProcessVolume"))
                                                                    .DesiredSizeOverride(FVector2D(16, 16))
                                                            ]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
                                                            [
                                                                SNew(STextBlock)
                                                                    .Text(FText::FromString("Post Process Volume"))
                                                                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
                                                            ]
                                                    ]
                                                    + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Exposure Bias: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(ExposureBiasBox, SEditableTextBox).Text(FText::FromString("0.0"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Saturation: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(SaturationBox, SEditableTextBox).Text(FText::FromString("1.0"))]
                                                    ]
                                                + SVerticalBox::Slot().AutoHeight().Padding(0, 2)
                                                    [
                                                        SNew(SHorizontalBox)
                                                            + SHorizontalBox::Slot().AutoWidth()
                                                            [SNew(STextBlock).Text(FText::FromString("Contrast: "))]
                                                            + SHorizontalBox::Slot().FillWidth(1.0f)
                                                            [SAssignNew(ContrastBox, SEditableTextBox).Text(FText::FromString("1.0"))]
                                                    ]
                                            ]
                                    ];

                                // ============================================
                                // КНОПКИ
                                // ============================================
                                Content->AddSlot().AutoHeight().Padding(10)
                                    [
                                        SNew(SHorizontalBox)
                                            + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0)
                                            [
                                                SNew(SButton)
                                                    .Text(FText::FromString("Apply to Scene"))
                                                    .OnClicked_Lambda([SunIntensityBox, SunTempBox, SunPitchBox, FogDensityBox, FogHeightFalloffBox, FogMaxOpacityBox, FogStartDistanceBox, VolumetricFogCheckBox, SkyIntensityBox, Window, ExposureBiasBox, SaturationBox, ContrastBox]()
                                                        {
                                                            if (!SunIntensityBox.IsValid()) return FReply::Handled();
                                                            FAtmospherePresetData Data;

                                                            Data.SunIntensity = FCString::Atof(*SunIntensityBox->GetText().ToString());
                                                            Data.SunTemperature = FCString::Atof(*SunTempBox->GetText().ToString());
                                                            Data.SunRotation = FRotator(FCString::Atof(*SunPitchBox->GetText().ToString()), 0.0f, 0.0f);
                                                            Data.FogDensity = FCString::Atof(*FogDensityBox->GetText().ToString());
                                                            Data.FogHeightFalloff = FCString::Atof(*FogHeightFalloffBox->GetText().ToString());
                                                            Data.FogMaxOpacity = FCString::Atof(*FogMaxOpacityBox->GetText().ToString());
                                                            Data.FogStartDistance = FCString::Atof(*FogStartDistanceBox->GetText().ToString());
                                                            bool bVolFog = false;
                                                            if (VolumetricFogCheckBox.IsValid())
                                                                bVolFog = (VolumetricFogCheckBox->GetCheckedState() == ECheckBoxState::Checked);
                                                            Data.bEnableVolumetricFog = bVolFog;
                                                            Data.FogColor = FLinearColor(0.5f, 0.6f, 0.8f);
                                                            Data.SkyLightIntensity = FCString::Atof(*SkyIntensityBox->GetText().ToString());
                                                            Data.ExposureBias = FCString::Atof(*ExposureBiasBox->GetText().ToString());
                                                            Data.Saturation = FCString::Atof(*SaturationBox->GetText().ToString());
                                                            Data.Contrast = FCString::Atof(*ContrastBox->GetText().ToString());

                                                            UAtmospherePreset::ApplyPresetData(Data);
                                                            return FReply::Handled();
                                                        })
                                            ]
                                        + SHorizontalBox::Slot().AutoWidth()
                                            [
                                                SNew(SButton)
                                                    .Text(FText::FromString("Reset to Default"))
                                                    .OnClicked_Lambda([SunIntensityBox, SunTempBox, SunPitchBox, FogDensityBox, FogHeightFalloffBox, FogMaxOpacityBox, FogStartDistanceBox, VolumetricFogCheckBox, SkyIntensityBox, Window, ExposureBiasBox, SaturationBox, ContrastBox]()
                                                        {
                                                            if (!SunIntensityBox.IsValid()) return FReply::Handled();
                                                            SunIntensityBox->SetText(FText::FromString("10.0"));
                                                            SunTempBox->SetText(FText::FromString("5500.0"));
                                                            SunPitchBox->SetText(FText::FromString("-45.0"));
                                                            FogDensityBox->SetText(FText::FromString("0.02"));
                                                            FogHeightFalloffBox->SetText(FText::FromString("0.2"));
                                                            FogMaxOpacityBox->SetText(FText::FromString("1.0"));
                                                            FogStartDistanceBox->SetText(FText::FromString("0.0"));
                                                            ExposureBiasBox->SetText(FText::FromString("0.0"));
                                                            SaturationBox->SetText(FText::FromString("1.0"));
                                                            ContrastBox->SetText(FText::FromString("1.0"));
                                                            if (VolumetricFogCheckBox.IsValid())
                                                                VolumetricFogCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
                                                            SkyIntensityBox->SetText(FText::FromString("1.0"));

                                                            FAtmospherePresetData Data;
                                                            Data.SunIntensity = 10.0f;
                                                            Data.SunTemperature = 5500.0f;
                                                            Data.SunRotation = FRotator(-45.0f, 0.0f, 0.0f);
                                                            Data.FogDensity = 0.02f;
                                                            Data.FogColor = FLinearColor(0.5f, 0.6f, 0.8f);
                                                            Data.FogHeightFalloff = 0.2f;
                                                            Data.FogMaxOpacity = 1.0f;
                                                            Data.FogStartDistance = 0.0f;
                                                            Data.bEnableVolumetricFog = false;
                                                            Data.SkyLightIntensity = 1.0f;
                                                            Data.ExposureBias = 0.0f;
                                                            Data.Saturation = 1.0f;
                                                            Data.Contrast = 1.0f;

                                                            UAtmospherePreset::ApplyPresetData(Data);
                                                            return FReply::Handled();
                                                        })
                                            ]
                                    
                                    ];
                                // Dev status
                                Content->AddSlot().AutoHeight().Padding(10, 5)
                                    [
                                        SNew(STextBlock)
                                            .Text(FText::FromString("Status: Ready"))
                                            .ColorAndOpacity(FLinearColor(0.2f, 0.8f, 0.2f))
                                    ];

                                Window->SetContent(ScrollContent);
                                FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
                                    TEXT("AtmosphereManualSetup"),
                                    FOnSpawnTab::CreateLambda([ScrollContent](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
                                        {
                                            return SNew(SDockTab)
                                                .TabRole(ETabRole::NomadTab)
                                                [
                                                    ScrollContent
                                                ];
                                        }))
                                    .SetDisplayName(FText::FromString("Atmosphere Manual Setup"));

                                FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("AtmosphereManualSetup")));
                            })
                    ))
                );
            })
    );
}

void FAtmosphereToolkitModule::ShutdownModule() {}

IMPLEMENT_MODULE(FAtmosphereToolkitModule, AtmosphereToolkit)