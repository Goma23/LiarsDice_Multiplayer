using UnrealBuildTool;
using System.Collections.Generic;

public class LiarsDiceEditorTarget : TargetRules
{
	public LiarsDiceEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		bOverrideBuildEnvironment = true;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("LiarsDice");
	}
}
