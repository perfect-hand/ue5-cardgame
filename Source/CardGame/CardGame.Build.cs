namespace UnrealBuildTool.Rules
{
	public class CardGame : ModuleRules
	{
		public CardGame(ReadOnlyTargetRules Target)
            : base(Target)
		{
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            bEnforceIWYU = true;

            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "CardGame/Private"
                });

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "GameplayTags"
                });
		}
	}
}
