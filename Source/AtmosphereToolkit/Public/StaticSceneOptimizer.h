// StaticSceneOptimizer.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticSceneOptimizer.generated.h"

UCLASS()
class ATMOSPHERETOOLKIT_API UStaticSceneOptimizer : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // 1. Auto Cull Distance - РАБОТАЕТ
    UFUNCTION(CallInEditor, Category = "Scene Optimizer")
    static void ApplyAutoCullDistanceToSelected();

    // 2. Convert to HISM - РАБОТАЕТ
    UFUNCTION(CallInEditor, Category = "Scene Optimizer")
    static void ConvertSelectedToHISM();

    // 3. World Partition Grid - РАБОТАЕТ
    UFUNCTION(CallInEditor, Category = "Scene Optimizer")
    static void OptimizeWorldPartitionGrid();

    // 4. Вспомогательная функция для конвертации списка актеров
    static void ConvertActorsToHISM(const TArray<AActor*>& Actors);

    // 5. Вспомогательная функция для получения выделенных актеров
    static TArray<AActor*> GetSelectedActors();
};