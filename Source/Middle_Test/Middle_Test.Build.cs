// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Middle_Test : ModuleRules
{
	public Middle_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Middle_Test",
			"Middle_Test/Variant_Platforming",
			"Middle_Test/Variant_Platforming/Animation",
			"Middle_Test/Variant_Combat",
			"Middle_Test/Variant_Combat/AI",
			"Middle_Test/Variant_Combat/Animation",
			"Middle_Test/Variant_Combat/Gameplay",
			"Middle_Test/Variant_Combat/Interfaces",
			"Middle_Test/Variant_Combat/UI",
			"Middle_Test/Variant_SideScrolling",
			"Middle_Test/Variant_SideScrolling/AI",
			"Middle_Test/Variant_SideScrolling/Gameplay",
			"Middle_Test/Variant_SideScrolling/Interfaces",
			"Middle_Test/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
