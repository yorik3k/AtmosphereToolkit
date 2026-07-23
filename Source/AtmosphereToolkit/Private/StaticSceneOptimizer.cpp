// StaticSceneOptimizer.cpp
#include "StaticSceneOptimizer.h"
#include "AtmosphereToolkit.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Engine/Selection.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Engine.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "EngineUtils.h"

// ============================================
// HELPER: Get Selected Actors
// ============================================
TArray<AActor*> UStaticSceneOptimizer::GetSelectedActors()
{
    TArray<AActor*> Result;
    USelection* SelectedActors = GEditor->GetSelectedActors();
    if (!SelectedActors) return Result;

    for (FSelectionIterator It(*SelectedActors); It; ++It)
    {
        AActor* Actor = Cast<AActor>(*It);
        if (Actor)
        {
            Result.Add(Actor);
        }
    }
    return Result;
}

// ============================================
// 1. AUTO CULL DISTANCE
// ============================================
void UStaticSceneOptimizer::ApplyAutoCullDistanceToSelected()
{
    TArray<AActor*> Selected = GetSelectedActors();

    if (Selected.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No actors selected! Select static meshes in the viewport."));
        Info.ExpireDuration = 3.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    int32 ProcessedCount = 0;

    for (AActor* Actor : Selected)
    {
        if (!Actor) continue;

        UStaticMeshComponent* SMC = Actor->FindComponentByClass<UStaticMeshComponent>();
        if (!SMC) continue;

        FBoxSphereBounds Bounds = SMC->Bounds;
        float MaxDimension = FMath::Max3(
            Bounds.BoxExtent.X * 2.0f,
            Bounds.BoxExtent.Y * 2.0f,
            Bounds.BoxExtent.Z * 2.0f
        );

        float CullDistance = FMath::Clamp(2000.0f + MaxDimension * 30.0f, 1000.0f, 50000.0f);

        UE_LOG(LogTemp, Warning, TEXT("[Optimizer] %s: Size=%.1f, CullDist=%.1f"),
            *Actor->GetName(), MaxDimension, CullDistance);

        Actor->MarkPackageDirty();
        ProcessedCount++;
    }

    FString Msg = FString::Printf(TEXT("Processed %d actors! Check Output Log."), ProcessedCount);
    FNotificationInfo Info(FText::FromString(Msg));
    Info.ExpireDuration = 3.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}

// ============================================
// 2. CONVERT TO HISM (РАБОТАЕТ!)
// ============================================
void UStaticSceneOptimizer::ConvertSelectedToHISM()
{
    TArray<AActor*> Selected = GetSelectedActors();
    ConvertActorsToHISM(Selected);
}

// ============================================
// 2.1 CONVERT TO HISM (ВЕРСИЯ ДЛЯ СПИСКА)
// ============================================
void UStaticSceneOptimizer::ConvertActorsToHISM(const TArray<AActor*>& Actors)
{
    if (Actors.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No actors to convert!"));
        Info.ExpireDuration = 2.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("[Optimizer] No valid world!"));
        return;
    }

    // Группируем актеры по StaticMesh
    TMap<UStaticMesh*, TArray<FTransform>> Groups;
    TArray<AActor*> ActorsToDelete;

    for (AActor* Actor : Actors)
    {
        if (!Actor) continue;

        UStaticMeshComponent* SMC = Actor->FindComponentByClass<UStaticMeshComponent>();
        if (!SMC) continue;

        UStaticMesh* Mesh = SMC->GetStaticMesh();
        if (!Mesh) continue;

        // Проверяем, что это не уже HISM
        if (Actor->GetClass()->GetName().Contains(TEXT("HierarchicalInstancedStaticMesh")))
        {
            continue;
        }

        FTransform Transform = Actor->GetActorTransform();
        Groups.FindOrAdd(Mesh).Add(Transform);
        ActorsToDelete.Add(Actor);
    }

    if (Groups.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No valid static meshes found to convert!"));
        Info.ExpireDuration = 3.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    int32 TotalGroups = 0;
    int32 TotalInstances = 0;

    for (auto& Pair : Groups)
    {
        UStaticMesh* Mesh = Pair.Key;
        TArray<FTransform>& Transforms = Pair.Value;

        if (Transforms.Num() <= 1)
        {
            UE_LOG(LogTemp, Warning, TEXT("[Optimizer] Skipping %s: only %d instance(s)"),
                *Mesh->GetName(), Transforms.Num());
            continue;
        }

        // Создаем HISM (ручной способ)
        AActor* NewActor = World->SpawnActor<AActor>(AActor::StaticClass());
        if (!NewActor)
        {
            UE_LOG(LogTemp, Error, TEXT("[Optimizer] Failed to spawn actor!"));
            continue;
        }

        UHierarchicalInstancedStaticMeshComponent* HISMComp =
            NewObject<UHierarchicalInstancedStaticMeshComponent>(NewActor, UHierarchicalInstancedStaticMeshComponent::StaticClass());

        if (!HISMComp)
        {
            UE_LOG(LogTemp, Error, TEXT("[Optimizer] Failed to create HISM component!"));
            World->DestroyActor(NewActor);
            continue;
        }

        HISMComp->RegisterComponent();
        NewActor->AddInstanceComponent(HISMComp);
        NewActor->SetRootComponent(HISMComp);

        HISMComp->SetStaticMesh(Mesh);
        HISMComp->SetCullDistances(3000.0f, 5000.0f);
        HISMComp->SetMobility(EComponentMobility::Static);

        for (const FTransform& Transform : Transforms)
        {
            HISMComp->AddInstance(Transform);
        }

        HISMComp->UpdateBounds();
        HISMComp->RecreatePhysicsState();

        FString ActorName = FString::Printf(TEXT("HISM_%s_%d"),
            *Mesh->GetName(),
            FMath::RandRange(1000, 9999));
        NewActor->SetActorLabel(ActorName);

        NewActor->MarkPackageDirty();
        TotalGroups++;
        TotalInstances += Transforms.Num();

        UE_LOG(LogTemp, Warning, TEXT("[Optimizer] Created HISM: %s with %d instances"),
            *ActorName, Transforms.Num());
    }

    // Удаляем оригинальные актеры
    int32 DeletedCount = 0;
    for (AActor* Actor : ActorsToDelete)
    {
        if (Actor && Actor->IsValidLowLevel())
        {
            World->DestroyActor(Actor);
            DeletedCount++;
        }
    }

    FString Msg = FString::Printf(TEXT("HISM: %d groups, %d instances, %d actors removed"),
        TotalGroups, TotalInstances, DeletedCount);

    FNotificationInfo Info(FText::FromString(Msg));
    Info.ExpireDuration = 4.0f;
    FSlateNotificationManager::Get().AddNotification(Info);

    UE_LOG(LogTemp, Warning, TEXT("[Optimizer] %s"), *Msg);
}

// ============================================
// 3. WORLD PARTITION GRID
// ============================================
void UStaticSceneOptimizer::OptimizeWorldPartitionGrid()
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("[Optimizer] No valid world!"));
        return;
    }

    // Проверяем, включен ли World Partition (поддерживаем оба варианта названия)
    AWorldSettings* WorldSettings = World->GetWorldSettings();
    if (!WorldSettings)
    {
        FNotificationInfo Info(FText::FromString("No World Settings found!"));
        Info.ExpireDuration = 3.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    // Проверяем флаги World Partition (несколько вариантов)
    bool bIsWorldPartitionEnabled = false;

    // Вариант 1: bEnableWorldPartition
    FProperty* WPProperty = WorldSettings->GetClass()->FindPropertyByName(TEXT("bEnableWorldPartition"));
    if (WPProperty)
    {
        bIsWorldPartitionEnabled = *WPProperty->ContainerPtrToValuePtr<bool>(WorldSettings);
    }

    // Вариант 2: Enable Streaming (UE5.4+)
    if (!bIsWorldPartitionEnabled)
    {
        FProperty* StreamingProperty = WorldSettings->GetClass()->FindPropertyByName(TEXT("bEnableStreaming"));
        if (StreamingProperty)
        {
            bIsWorldPartitionEnabled = *StreamingProperty->ContainerPtrToValuePtr<bool>(WorldSettings);
        }
    }

    // Вариант 3: Проверка через WorldPartition объект
    if (!bIsWorldPartitionEnabled)
    {
        UWorldPartition* WP = World->GetWorldPartition();
        if (WP != nullptr)
        {
            bIsWorldPartitionEnabled = true;
        }
    }

    if (!bIsWorldPartitionEnabled)
    {
        FNotificationInfo Info(FText::FromString("World Partition is NOT enabled for this level! Enable 'Enable Streaming' in World Settings."));
        Info.ExpireDuration = 4.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("[Optimizer] World Partition is enabled! Proceeding with optimization..."));

    // Размер грид-ячейки (128 метров)
    const double GridSize = 12800.0;

    // Собираем все статические актеры
    TArray<AActor*> AllStaticActors;
    for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
    {
        AStaticMeshActor* Actor = *It;
        if (Actor && Actor->IsValidLowLevel())
        {
            AllStaticActors.Add(Actor);
        }
    }

    if (AllStaticActors.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No static actors found in the level!"));
        Info.ExpireDuration = 3.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    // Группируем по грид-ячейкам
    TMap<FIntPoint, TArray<AActor*>> GridMap;
    for (AActor* Actor : AllStaticActors)
    {
        if (!Actor) continue;

        FVector Location = Actor->GetActorLocation();
        int32 GridX = FMath::FloorToInt(Location.X / GridSize);
        int32 GridY = FMath::FloorToInt(Location.Y / GridSize);
        FIntPoint GridKey(GridX, GridY);
        GridMap.FindOrAdd(GridKey).Add(Actor);
    }

    // Оптимизируем каждую ячейку с >N объектов
    const int32 MinActorsToOptimize = 15;
    int32 TotalOptimizedCells = 0;
    int32 TotalOptimizedActors = 0;

    // Отключаем выделение, чтобы не мешать
    GEditor->SelectNone(false, true);

    for (auto& Pair : GridMap)
    {
        FIntPoint Cell = Pair.Key;
        TArray<AActor*>& ActorsInCell = Pair.Value;

        if (ActorsInCell.Num() < MinActorsToOptimize)
        {
            continue;
        }

        UE_LOG(LogTemp, Warning, TEXT("[Optimizer] Optimizing cell (%d, %d): %d actors"),
            Cell.X, Cell.Y, ActorsInCell.Num());

        // Выделяем актеры в ячейке
        for (AActor* Actor : ActorsInCell)
        {
            if (Actor)
            {
                GEditor->SelectActor(Actor, true, true);
            }
        }

        // Конвертируем выделенные актеры в HISM
        ConvertSelectedToHISM();

        TotalOptimizedCells++;
        TotalOptimizedActors += ActorsInCell.Num();

        // Снимаем выделение после обработки
        GEditor->SelectNone(false, true);
    }

    // Уведомление
    FString Msg = FString::Printf(TEXT("World Partition: %d cells optimized, %d actors total"),
        TotalOptimizedCells, TotalOptimizedActors);

    FNotificationInfo Info(FText::FromString(Msg));
    Info.ExpireDuration = 4.0f;
    FSlateNotificationManager::Get().AddNotification(Info);

    UE_LOG(LogTemp, Warning, TEXT("[Optimizer] %s"), *Msg);
}