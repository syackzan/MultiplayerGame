// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PuzzlePlatformM : ModuleRules
{
	public PuzzlePlatformM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"UMG", 
			"OnlineSubsystem", 
			"OnlineSubsystemSteam", //Provides Online SusbsystemSteam
			"OnlineSubsystemUtils", //Provides utils to acquire Steam Id
			"Steamworks" //Provides utils to acquire Steam Id
		});
	}
}
