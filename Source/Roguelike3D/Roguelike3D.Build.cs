// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Roguelike3D : ModuleRules
{
	public Roguelike3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
