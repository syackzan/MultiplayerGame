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
			"EnhancedInput", //Enhanced Input
			"UMG", //Widgets
			"OnlineSubsystem", //Null subsytem testing
			"OnlineSubsystemSteam", //Provides Online SusbsystemSteam
			"OnlineSubsystemUtils", //Provides utils to acquire Steam Id
			"Steamworks", //Provides utils to acquire Steam Id
			"HTTP", //Query HTTP Requests
			"Json" //Json manipulation
		});
	}
}
