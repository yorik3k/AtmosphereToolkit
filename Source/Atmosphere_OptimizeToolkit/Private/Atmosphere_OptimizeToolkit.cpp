#include "Atmosphere_OptimizeToolkit.h"
#include "ToolMenus.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Editor.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#define LOCTEXT_NAMESPACE "FAtmosphere_OptimizeToolkitModule"

void FAtmosphere_OptimizeToolkitModule::StartupModule()
{
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateLambda([]()
            {
                UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");

                // ============================================
                // СЕКЦИЯ "Atmosphere Optimize Toolkit"
                // ============================================
                FToolMenuSection& Section = Menu->AddSection(
                    "AtmosphereTools",
                    FText::FromString("Atmosphere Optimize Toolkit")
                );

                // ============================================
                // КНОПКА 1: ATMOSPHERE
                // ============================================
                Section.AddMenuEntry(
                    "AtmosphereEditor",
                    FText::FromString("☀️ Atmosphere Editor"),
                    FText::FromString("Open atmosphere presets and manual settings"),
                    FSlateIcon(),
                    FToolUIActionChoice(FUIAction(
                        FExecuteAction::CreateLambda([]()
                            {
                                UClass* WidgetClass = LoadClass<UUserWidget>(
                                    nullptr,
                                    TEXT("/Atmosphere_OptimizeToolkit/Widgets/WBP_AtmosphereEditor.WBP_AtmosphereEditor_C")
                                );

                                if (WidgetClass)
                                {
                                    TSharedRef<SWindow> Window = SNew(SWindow)
                                        .Title(FText::FromString("Atmosphere Editor"))
                                        .ClientSize(FVector2D(1920, 1080))
                                        .SizingRule(ESizingRule::UserSized)
                                        .SupportsMinimize(true)
                                        .SupportsMaximize(false);

                                    UWorld* World = GEditor->GetEditorWorldContext().World();
                                    UUserWidget* Widget = CreateWidget<UUserWidget>(World, WidgetClass);

                                    if (Widget)
                                    {
                                        Window->SetContent(Widget->TakeWidget());
                                    }

                                    FSlateApplication::Get().AddWindow(Window);
                                }
                                else
                                {
                                    FNotificationInfo Info(FText::FromString("Failed to load WBP_AtmosphereEditor!"));
                                    Info.ExpireDuration = 3.0f;
                                    FSlateNotificationManager::Get().AddNotification(Info);
                                }
                            })
                    ))
                );

                // ============================================
                // КНОПКА 2: OPTIMIZER
                // ============================================
                Section.AddMenuEntry(
                    "OptimizerEditor",
                    FText::FromString("⚡ Scene Optimizer"),
                    FText::FromString("Open scene optimization tools"),
                    FSlateIcon(),
                    FToolUIActionChoice(FUIAction(
                        FExecuteAction::CreateLambda([]()
                            {
                                UClass* WidgetClass = LoadClass<UUserWidget>(
                                    nullptr,
                                    TEXT("/Atmosphere_OptimizeToolkit/Widgets/WBP_OptimizerEditor.WBP_OptimizerEditor_C")
                                );

                                if (WidgetClass)
                                {
                                    TSharedRef<SWindow> Window = SNew(SWindow)
                                        .Title(FText::FromString("Scene Optimizer"))
                                        .ClientSize(FVector2D(600, 400))
                                        .SizingRule(ESizingRule::UserSized)
                                        .SupportsMinimize(true)
                                        .SupportsMaximize(false);

                                    UWorld* World = GEditor->GetEditorWorldContext().World();
                                    UUserWidget* Widget = CreateWidget<UUserWidget>(World, WidgetClass);

                                    if (Widget)
                                    {
                                        Window->SetContent(Widget->TakeWidget());
                                    }

                                    FSlateApplication::Get().AddWindow(Window);
                                }
                                else
                                {
                                    FNotificationInfo Info(FText::FromString("Failed to load WBP_OptimizerEditor!"));
                                    Info.ExpireDuration = 3.0f;
                                    FSlateNotificationManager::Get().AddNotification(Info);
                                }
                            })
                    ))
                );
            })
    );
}

void FAtmosphere_OptimizeToolkitModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAtmosphere_OptimizeToolkitModule, Atmosphere_OptimizeToolkit)