// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SmartFactory : ModuleRules
{
	public SmartFactory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "UMG" , "EnhancedInput", "Json", "HTTP", "Networking", "Sockets", "JsonUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] { "HTTP", "Json" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
