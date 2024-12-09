// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CMP407Project : ModuleRules
{
	public CMP407Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
