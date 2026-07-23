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
            "Engine",          // <--- ÂÑÅ ÊËÀÑÑÛ HISM ÓÆÅ ÇÄÅÑÜ
            "UnrealEd",
            "ToolMenus",
            "Slate",
            "SlateCore",
            "EditorStyle",
            "InputCore"
        });

        // PrivateDependencyModuleNames ÍÅ ÍÓÆÅÍ!
        // Îñòàâëÿåì ïóñòûì èëè óäàëÿåì
    }
}