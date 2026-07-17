using UnrealBuildTool;

public class AtmosphereToolkit : ModuleRules
{
    public AtmosphereToolkit(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "ToolMenus",
            "Slate",
            "SlateCore"
        });
    }
}