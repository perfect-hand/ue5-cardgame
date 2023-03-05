#include "GameplayTagsManager.h"
#include "Misc/AutomationTest.h"

#include "Model/CardGameModel.h"
#include "Services/CardGameGameplayTagService.h"

namespace CardGameGameplayTagServiceTest
{
	struct FNativeGameplayTags : FGameplayTagNativeAdder
	{
		FGameplayTag TestTagA;
		FGameplayTag TestTagB;
		
		virtual void AddTags() override
		{
			UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
			TestTagA = Manager.AddNativeGameplayTag(TEXT("CardGameGameplayTagServiceTest.TestTag.A"));
			TestTagB = Manager.AddNativeGameplayTag(TEXT("CardGameGameplayTagServiceTest.TestTag.B"));
		}

		FORCEINLINE static const FNativeGameplayTags& Get()
		{
			return StaticInstance;
		}
		static FNativeGameplayTags StaticInstance;
	};
	FNativeGameplayTags FNativeGameplayTags::StaticInstance;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetCardGameplayTagsTest, "CardGame.GameplayTagService.GetCardGameplayTags", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FGetCardGameplayTagsTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	const FGameplayTag TestTagA = CardGameGameplayTagServiceTest::FNativeGameplayTags::Get().TestTagA;
	const FGameplayTag TestTagB = CardGameGameplayTagServiceTest::FNativeGameplayTags::Get().TestTagB;

	FCardGameModel GameModel;
	GameModel.GlobalModel.GameplayTags.AddTag(TestTagA);

	FCardGameCardModel CardModel;
	CardModel.CardModel.GameplayTags.AddTag(TestTagB);
	
	// ACT
	constexpr FCardGameGameplayTagService GameplayTagService;
	FGameplayTagContainer CombinedTags = GameplayTagService.GetCardGameplayTags(GameModel, CardModel);

	// ASSERT
	TestTrue(TEXT("CombinedTags Has Test Tag A"), CombinedTags.HasTag(TestTagA));
	TestTrue(TEXT("CombinedTags Has Test Tag B"), CombinedTags.HasTag(TestTagB));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddGlobalGameplayTagTest, "CardGame.GameplayTagService.AddGlobalGameplayTag", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddGlobalGameplayTagTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	const FGameplayTag TestTag = CardGameGameplayTagServiceTest::FNativeGameplayTags::Get().TestTagA;
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
	const FGameplayTag TestTag = CardGameGameplayTagServiceTest::FNativeGameplayTags::Get().TestTagA;

	FCardGameModel Model;
	Model.GlobalModel.GameplayTags.AddTag(TestTag);
	
	// ACT
	constexpr FCardGameGameplayTagService GameplayTagService;
	GameplayTagService.RemoveGlobalGameplayTag(Model, TestTag);

	// ASSERT
	TestTrue(TEXT("Test Tag Removed"), !Model.GlobalModel.GameplayTags.HasTag(TestTag));
	return true;
}
