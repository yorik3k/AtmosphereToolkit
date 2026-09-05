#include "StaticSceneOptimizer.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Engine/Selection.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

TArray<AActor*> UStaticSceneOptimizer::GetSelectedActors()
{
    TArray<AActor*> Result;
    if (!GEditor) return Result;

    USelection* SelectedActors = GEditor->GetSelectedActors();
    if (!SelectedActors) return Result;

    // UE 5.5+ способ
    TArray<UObject*> SelectedObjects;
    SelectedActors->GetSelectedObjects(SelectedObjects);

    for (UObject* Obj : SelectedObjects)
    {
        if (AActor* Actor = Cast<AActor>(Obj))
        {
            Result.Add(Actor);
        }
    }
    return Result;
}

void UStaticSceneOptimizer::ApplyAutoCullDistanceToSelected()
{
    TArray<AActor*> Selected = GetSelectedActors();
    if (Selected.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No actors selected!"));
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

    FString Msg = FString::Printf(TEXT("Processed %d actors!"), ProcessedCount);
    FNotificationInfo Info(FText::FromString(Msg));
    Info.ExpireDuration = 3.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}

void UStaticSceneOptimizer::ConvertSelectedToHISM()
{
    TArray<AActor*> Selected = GetSelectedActors();
    ConvertActorsToHISM(Selected);
}

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
    if (!World) return;

    TMap<UStaticMesh*, TArray<FTransform>> Groups;
    TArray<AActor*> ActorsToDelete;

    for (AActor* Actor : Actors)
    {
        if (!Actor) continue;
        UStaticMeshComponent* SMC = Actor->FindComponentByClass<UStaticMeshComponent>();
        if (!SMC) continue;
        UStaticMesh* Mesh = SMC->GetStaticMesh();
        if (!Mesh) continue;
        if (Actor->GetClass()->GetName().Contains(TEXT("HierarchicalInstancedStaticMesh"))) continue;

        Groups.FindOrAdd(Mesh).Add(Actor->GetActorTransform());
        ActorsToDelete.Add(Actor);
    }

    if (Groups.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No valid static meshes found!"));
        Info.ExpireDuration = 3.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    int32 TotalGroups = 0, TotalInstances = 0;
    for (auto& Pair : Groups)
    {
        UStaticMesh* Mesh = Pair.Key;
        TArray<FTransform>& Transforms = Pair.Value;
        if (Transforms.Num() <= 1) continue;

        FTransform FirstTransform = Transforms[0];
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AActor* NewActor = World->SpawnActor<AActor>(AActor::StaticClass(), FirstTransform.GetLocation(), FirstTransform.GetRotation().Rotator(), SpawnParams);
        NewActor->SetActorScale3D(FirstTransform.GetScale3D());
        if (!NewActor) continue;

        UHierarchicalInstancedStaticMeshComponent* HISMComp =
            NewObject<UHierarchicalInstancedStaticMeshComponent>(NewActor, UHierarchicalInstancedStaticMeshComponent::StaticClass());
        if (!HISMComp)
        {
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

        FString ActorName = FString::Printf(TEXT("HISM_%s_%d"), *Mesh->GetName(), FMath::RandRange(1000, 9999));
        NewActor->SetActorLabel(ActorName);
        NewActor->MarkPackageDirty();

        TotalGroups++;
        TotalInstances += Transforms.Num();
        UE_LOG(LogTemp, Warning, TEXT("[Optimizer] Created HISM: %s with %d instances"), *ActorName, Transforms.Num());
    }

    for (AActor* Actor : ActorsToDelete)
    {
        if (Actor && Actor->IsValidLowLevel())
        {
            World->DestroyActor(Actor);
        }
    }

    FString Msg = FString::Printf(TEXT("HISM: %d groups, %d instances"), TotalGroups, TotalInstances);
    FNotificationInfo Info(FText::FromString(Msg));
    Info.ExpireDuration = 4.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}

void UStaticSceneOptimizer::OptimizeWorldPartitionGrid()
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("[Optimizer] No valid world!"));
        return;
    }

    AWorldSettings* WorldSettings = World->GetWorldSettings();
    if (!WorldSettings) return;

    bool bIsWorldPartitionEnabled = false;
    FProperty* WPProperty = WorldSettings->GetClass()->FindPropertyByName(TEXT("bEnableWorldPartition"));
    if (WPProperty)
    {
        bIsWorldPartitionEnabled = *WPProperty->ContainerPtrToValuePtr<bool>(WorldSettings);
    }

    if (!bIsWorldPartitionEnabled)
    {
        FProperty* StreamingProperty = WorldSettings->GetClass()->FindPropertyByName(TEXT("bEnableStreaming"));
        if (StreamingProperty)
        {
            bIsWorldPartitionEnabled = *StreamingProperty->ContainerPtrToValuePtr<bool>(WorldSettings);
        }
    }

    if (!bIsWorldPartitionEnabled)
    {
        UWorldPartition* WP = World->GetWorldPartition();
        if (WP) bIsWorldPartitionEnabled = true;
    }

    if (!bIsWorldPartitionEnabled)
    {
        FNotificationInfo Info(FText::FromString("World Partition is NOT enabled!"));
        Info.ExpireDuration = 4.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    const double GridSize = 12800.0;
    TArray<AActor*> AllStaticActors;
    for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
    {
        if (*It && (*It)->IsValidLowLevel())
        {
            AllStaticActors.Add(*It);
        }
    }

    if (AllStaticActors.Num() == 0)
    {
        FNotificationInfo Info(FText::FromString("No static actors found!"));
        Info.ExpireDuration = 3.0f;
        FSlateNotificationManager::Get().AddNotification(Info);
        return;
    }

    TMap<FIntPoint, TArray<AActor*>> GridMap;
    for (AActor* Actor : AllStaticActors)
    {
        if (!Actor) continue;
        FVector Location = Actor->GetActorLocation();
        FIntPoint GridKey(
            FMath::FloorToInt(Location.X / GridSize),
            FMath::FloorToInt(Location.Y / GridSize)
        );
        GridMap.FindOrAdd(GridKey).Add(Actor);
    }

    const int32 MinActorsToOptimize = 15;
    int32 TotalOptimizedCells = 0;
    int32 TotalOptimizedActors = 0;

    GEditor->SelectNone(false, true);

    for (auto& Pair : GridMap)
    {
        FIntPoint Cell = Pair.Key;
        TArray<AActor*>& ActorsInCell = Pair.Value;

        if (ActorsInCell.Num() < MinActorsToOptimize) continue;

        for (AActor* Actor : ActorsInCell)
        {
            if (Actor) GEditor->SelectActor(Actor, true, true);
        }

        ConvertSelectedToHISM();
        TotalOptimizedCells++;
        TotalOptimizedActors += ActorsInCell.Num();
        GEditor->SelectNone(false, true);
    }

    FString Msg = FString::Printf(TEXT("Optimized %d cells, %d actors"), TotalOptimizedCells, TotalOptimizedActors);
    FNotificationInfo Info(FText::FromString(Msg));
    Info.ExpireDuration = 4.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}