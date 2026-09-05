#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticSceneOptimizer.generated.h"

UCLASS()
class ATMOSPHERE_OPTIMIZETOOLKIT_API UStaticSceneOptimizer : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(CallInEditor, Category = "Scene Optimizer")
    static void ApplyAutoCullDistanceToSelected();

    UFUNCTION(CallInEditor, Category = "Scene Optimizer")
    static void ConvertSelectedToHISM();

    UFUNCTION(CallInEditor, Category = "Scene Optimizer")
    static void OptimizeWorldPartitionGrid();

    static void ConvertActorsToHISM(const TArray<AActor*>& Actors);
    static TArray<AActor*> GetSelectedActors();
};