using UnrealBuildTool;

public class Atmosphere_OptimizeToolkit : ModuleRules
{
    public Atmosphere_OptimizeToolkit(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "ToolMenus",
                "EditorWidgets",
                "Projects"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",
                "InputCore",
                "AssetRegistry"
            }
        );
    }
}