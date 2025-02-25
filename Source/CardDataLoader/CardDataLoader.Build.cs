using UnrealBuildTool;

public class CardDataLoader : ModuleRules
{
    public CardDataLoader(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        OptimizeCode = CodeOptimization.Never;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "HTTP", 
                "Json", 
                "Engine",
                "UnrealEd",
                "UMG",
                "Blutility",
                "DeveloperSettings",
                "CardData"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "JsonUtilities",
                "ScriptableEditorWidgets", 
                "EditorScriptingUtilities"
            }
        );
    }
}