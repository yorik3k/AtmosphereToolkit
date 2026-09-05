#include "OptimizerEditorWidget.h"
#include "StaticSceneOptimizer.h"

void UOptimizerEditorWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (AutoCullButton)
    {
        AutoCullButton->OnClicked.AddDynamic(this, &UOptimizerEditorWidget::OnAutoCullClicked);
    }

    if (ConvertHISMButton)
    {
        ConvertHISMButton->OnClicked.AddDynamic(this, &UOptimizerEditorWidget::OnConvertHISMClicked);
    }

    if (OptimizeWPButton)
    {
        OptimizeWPButton->OnClicked.AddDynamic(this, &UOptimizerEditorWidget::OnOptimizeWPClicked);
    }

    UpdateStatus(TEXT("Ready"));
}

void UOptimizerEditorWidget::OnAutoCullClicked()
{
    UStaticSceneOptimizer::ApplyAutoCullDistanceToSelected();
    UpdateStatus(TEXT("Auto Cull Distance applied!"));
}

void UOptimizerEditorWidget::OnConvertHISMClicked()
{
    UStaticSceneOptimizer::ConvertSelectedToHISM();
    UpdateStatus(TEXT("Converted to HISM!"));
}

void UOptimizerEditorWidget::OnOptimizeWPClicked()
{
    UStaticSceneOptimizer::OptimizeWorldPartitionGrid();
    UpdateStatus(TEXT("World Partition optimized!"));
}

void UOptimizerEditorWidget::UpdateStatus(const FString& Message)
{
    if (StatusTextBlock)
    {
        StatusTextBlock->SetText(FText::FromString(Message));
    }
}