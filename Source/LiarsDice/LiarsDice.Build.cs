using UnrealBuildTool;

public class LiarsDice : ModuleRules
{
	public LiarsDice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "OnlineSubsystem", "OnlineSubsystemUtils", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
