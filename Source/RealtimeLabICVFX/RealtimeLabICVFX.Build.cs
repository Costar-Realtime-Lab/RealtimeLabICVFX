// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RealtimeLabICVFX : ModuleRules
{
	public RealtimeLabICVFX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
            {
                "Core",
                "CoreUObject",
				"Engine",

                "MoSysAPI",
                "MoSysTracking",
                "MoSysLensDistortion",
                "CanonLiveLinkPlugin",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"DeveloperSettings",
			}
		);
	}
}
