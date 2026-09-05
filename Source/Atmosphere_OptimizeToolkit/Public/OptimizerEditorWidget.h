#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StaticSceneOptimizer.h"
#include "OptimizerEditorWidget.generated.h"

UCLASS()
class ATMOSPHERE_OPTIMIZETOOLKIT_API UOptimizerEditorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* AutoCullButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ConvertHISMButton;

    UPROPERTY(meta = (BindWidget))
    UButton* OptimizeWPButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* StatusTextBlock;

private:
    UFUNCTION()
    void OnAutoCullClicked();

    UFUNCTION()
    void OnConvertHISMClicked();

    UFUNCTION()
    void OnOptimizeWPClicked();

    void UpdateStatus(const FString& Message);
};