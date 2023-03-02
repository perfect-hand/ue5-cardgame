#include "GameplayTagsManager.h"
#include "Misc/AutomationTest.h"

#include "Model/CardGameModel.h"
#include "Services/CardGameGameplayTagService.h"

namespace CardGameGameplayTagServiceTest
{
	struct FNativeGameplayTags : public FGameplayTagNativeAdder
	{
		FGameplayTag TestTag;

		virtual void AddTags() override
		{
			UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
			TestTag = Manager.AddNativeGameplayTag(TEXT("CardGameGameplayTagServiceTest.TestTag"));
		}

		FORCEINLINE static const FNativeGameplayTags& Get()
		{
			return StaticInstance;
		}
		static FNativeGameplayTags StaticInstance;
	};
	FNativeGameplayTags FNativeGameplayTags::StaticInstance;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddGlobalGameplayTagTest, "CardGame.GameplayTagService.AddGlobalGameplayTag", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddGlobalGameplayTagTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	const FGameplayTag TestTag = CardGameGameplayTagServiceTest::FNativeGameplayTags::Get().TestTag;
	FCardGameModel Model;
	
	// ACT
	constexpr FCardGameGameplayTagService GameplayTagService;
	GameplayTagService.AddGlobalGameplayTag(Model, TestTag);

	// ASSERT
	TestTrue(TEXT("Test Tag Added"), Model.GlobalModel.GameplayTags.HasTag(TestTag));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRemoveGlobalGameplayTagTest, "CardGame.GameplayTagService.RemoveGlobalGameplayTag", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FRemoveGlobalGameplayTagTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	const FGameplayTag TestTag = CardGameGameplayTagServiceTest::FNativeGameplayTags::Get().TestTag;

	FCardGameModel Model;
	Model.GlobalModel.GameplayTags.AddTag(TestTag);
	
	// ACT
	constexpr FCardGameGameplayTagService GameplayTagService;
	GameplayTagService.RemoveGlobalGameplayTag(Model, TestTag);

	// ASSERT
	TestTrue(TEXT("Test Tag Removed"), !Model.GlobalModel.GameplayTags.HasTag(TestTag));
	return true;
}
