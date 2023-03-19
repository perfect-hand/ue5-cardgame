#include "Misc/AutomationTest.h"

#include "GameplayTagsManager.h"

#include "Assets/CardGameAttribute.h"
#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "Assets/CardGameConfiguration.h"
#include "Model/CardGameModel.h"
#include "Providers/CardGameRandomNumberProvider.h"
#include "Services/CardGameCardPileService.h"

namespace CardGameCardPileServiceTest
{
	class FOnCardAddedToGlobalCardPileTestEventHandler
	{
	public:
		UCardGameCardPile* CardPileClass;
		int32 PositionInCardPile;
		FCardGameCardModel Card;
		
		void OnCardAddedToGlobalCardPile(UCardGameCardPile* InCardPileClass, int32 InPositionInCardPile, FCardGameCardModel InCard)
		{
			CardPileClass = InCardPileClass;
			PositionInCardPile = InPositionInCardPile;
			Card = InCard;
		}
	};

	class FOnCardAddedToPlayerCardPileTestEventHandler
	{
	public:
		uint8 PlayerIndex;
		UCardGameCardPile* CardPileClass;
		int32 PositionInCardPile;
		FCardGameCardModel Card;
		
		void OnCardAddedToPlayerCardPile(uint8 InPlayerIndex, UCardGameCardPile* InCardPileClass, int32 InPositionInCardPile, FCardGameCardModel InCard)
		{
			PlayerIndex = InPlayerIndex;
			CardPileClass = InCardPileClass;
			PositionInCardPile = InPositionInCardPile;
			Card = InCard;
		}
	};
	
	struct FNativeGameplayTags : FGameplayTagNativeAdder
	{
		FGameplayTag TestTagA;
		FGameplayTag TestTagB;
	
		virtual void AddTags() override
		{
			UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
			TestTagA = Manager.AddNativeGameplayTag(TEXT("CardGameCardPileServiceTest.TestTag.A"));
			TestTagB = Manager.AddNativeGameplayTag(TEXT("CardGameCardPileServiceTest.TestTag.B"));
		}

		FORCEINLINE static const FNativeGameplayTags& Get()
		{
			return StaticInstance;
		}
		static FNativeGameplayTags StaticInstance;
	};
	FNativeGameplayTags FNativeGameplayTags::StaticInstance;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetCardModelByInstanceIdGetsGlobalCardTest, "CardGame.CardPileService.GetCardModelByInstanceIdGetsGlobalCard", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FGetCardModelByInstanceIdGetsGlobalCardTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	Model.GlobalCardPiles.Add(TestCardPile);

	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();
	
	FCardGameCardModel TestCard;
	TestCard.InstanceId = Model.Cards.Num();
	TestCard.CardClass = TestCardClass;

	int64 InstanceId = Model.Cards.Add(TestCard);
	Model.GlobalCardPiles[0].Cards.Add(InstanceId);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	TOptional<FCardGameCardModel> FoundCard = CardPileService.GetCardModelByInstanceId(Model, TestCard.InstanceId);
	
	// ASSERT
	TestTrue(TEXT("Has Found Card"), FoundCard.IsSet());
	TestEqual(TEXT("Card Instance Id"), FoundCard.GetValue().InstanceId, 0LL);
	TestEqual(TEXT("Card Class"), FoundCard.GetValue().CardClass, TestCardClass);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetCardModelByInstanceIdGetsPlayerCardTest, "CardGame.CardPileService.GetCardModelByInstanceIdGetsPlayerCard", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FGetCardModelByInstanceIdGetsPlayerCardTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	
	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	Player.PlayerCardPiles.Add(TestCardPile);
	Model.Players.Add(Player);

	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();
	
	FCardGameCardModel TestCard;
	TestCard.InstanceId = Model.Cards.Num();
	TestCard.CardClass = TestCardClass;

	int64 InstanceId = Model.Cards.Add(TestCard);
	Model.Players[0].PlayerCardPiles[0].Cards.Add(InstanceId);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	TOptional<FCardGameCardModel> FoundCard = CardPileService.GetCardModelByInstanceId(Model, TestCard.InstanceId);
	
	// ASSERT
	TestTrue(TEXT("Has Found Card"), FoundCard.IsSet());
	TestEqual(TEXT("Card Instance Id"), FoundCard.GetValue().InstanceId, 0LL);
	TestEqual(TEXT("Card Class"), FoundCard.GetValue().CardClass, TestCardClass);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddGlobalCardPilesTest, "CardGame.CardPileService.AddGlobalCardPiles", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddGlobalCardPilesTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	UCardGameCardPile* TestCardPile0 = NewObject<UCardGameCardPile>();
	UCardGameCardPile* TestCardPile1 = NewObject<UCardGameCardPile>();
	
	TArray<UCardGameCardPile*> CardPileClasses;
	CardPileClasses.Add(TestCardPile0);
	CardPileClasses.Add(TestCardPile1);
	
	UCardGameConfiguration* Configuration = NewObject<UCardGameConfiguration>();
	Configuration->SetGlobalCardPileClasses(CardPileClasses);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddGlobalCardPiles(Model, Configuration);
	
	// ASSERT
	TestEqual(TEXT("Num Global Card Piles"), Model.GlobalCardPiles.Num(), 2);
	TestEqual(TEXT("Global Card Pile 0"), Model.GlobalCardPiles[0].CardPileClass, TestCardPile0);
	TestEqual(TEXT("Global Card Pile 1"), Model.GlobalCardPiles[1].CardPileClass, TestCardPile1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToGlobalCardPileSetsCardClassTest, "CardGame.CardPileService.AddCardToGlobalCardPileSetsCardClass", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToGlobalCardPileSetsCardClassTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	Model.GlobalCardPiles.Add(TestCardPile);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Card Class"), Model.Cards[0].CardClass, TestCard);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToGlobalCardPileSetsAttributesTest, "CardGame.CardPileService.AddCardToGlobalCardPileSetsAttributes", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToGlobalCardPileSetsAttributesTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	Model.GlobalCardPiles.Add(TestCardPile);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();

	UCardGameAttribute* TestAttribute1 = NewObject<UCardGameAttribute>();
	UCardGameAttribute* TestAttribute2 = NewObject<UCardGameAttribute>();
	
	TMap<UCardGameAttribute*, int32> InitialAttributes;
	InitialAttributes.Add(TestAttribute1, 2);
	InitialAttributes.Add(TestAttribute2, 3);
	TestCard->SetInitialAttributes(InitialAttributes);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Num Attributes"), Model.Cards[0].CardModel.Attributes.Num(), 2);
	TestEqual(TEXT("Attribute 1 Class"), Model.Cards[0].CardModel.Attributes[0].Attribute, TestAttribute1);
	TestEqual(TEXT("Attribute 1 Value"), Model.Cards[0].CardModel.Attributes[0].Value, 2);
	TestEqual(TEXT("Attribute 2 Class"), Model.Cards[0].CardModel.Attributes[1].Attribute, TestAttribute2);
	TestEqual(TEXT("Attribute 2 Value"), Model.Cards[0].CardModel.Attributes[1].Value, 3);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToGlobalCardPileSetsGameplayTagsTest, "CardGame.CardPileService.AddCardToGlobalCardPileSetsGameplayTags", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToGlobalCardPileSetsGameplayTagsTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	Model.GlobalCardPiles.Add(TestCardPile);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	const FGameplayTag TestTagA = CardGameCardPileServiceTest::FNativeGameplayTags::Get().TestTagA;
	const FGameplayTag TestTagB = CardGameCardPileServiceTest::FNativeGameplayTags::Get().TestTagB;

	FGameplayTagContainer TestGameplayTags;
	TestGameplayTags.AddTag(TestTagA);
	TestGameplayTags.AddTag(TestTagB);
	TestCard->SetInitialGameplayTags(TestGameplayTags);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestTrue(TEXT("Card Has Gameplay Tag A"), Model.Cards[0].CardModel.GameplayTags.HasTag(TestTagA));
	TestTrue(TEXT("Card Has Gameplay Tag A"), Model.Cards[0].CardModel.GameplayTags.HasTag(TestTagB));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToGlobalCardPileRaisesEventTest, "CardGame.CardPileService.AddCardToGlobalCardPileRaisesEvent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToGlobalCardPileRaisesEventTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	Model.GlobalCardPiles.Add(TestCardPile);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	FCardGameCardPileService CardPileService(RandomNumberProvider);

	CardGameCardPileServiceTest::FOnCardAddedToGlobalCardPileTestEventHandler TestEventHandler;
	CardPileService.OnCardAddedToGlobalCardPile.AddRaw(&TestEventHandler,
		&CardGameCardPileServiceTest::FOnCardAddedToGlobalCardPileTestEventHandler::OnCardAddedToGlobalCardPile);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Event Card Pile Class"), TestEventHandler.CardPileClass, TestCardPileClass);
	TestEqual(TEXT("Event Card Class"), TestEventHandler.Card.CardClass, TestCard);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToPlayerCardPileSetsCardClassTest, "CardGame.CardPileService.AddCardToPlayerCardPileSetsCardClass", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToPlayerCardPileSetsCardClassTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	Player.PlayerCardPiles.Add(TestCardPile);
	Model.Players.Add(Player);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddCardToPlayerCardPile(Model, Player.PlayerIndex, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Card Class"), Model.Cards[0].CardClass, TestCard);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToPlayerCardPileSetsAttributesTest, "CardGame.CardPileService.AddCardToPlayerCardPileSetsAttributes", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToPlayerCardPileSetsAttributesTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	Player.PlayerCardPiles.Add(TestCardPile);
	Model.Players.Add(Player);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();

	UCardGameAttribute* TestAttribute1 = NewObject<UCardGameAttribute>();
	UCardGameAttribute* TestAttribute2 = NewObject<UCardGameAttribute>();
	
	TMap<UCardGameAttribute*, int32> InitialAttributes;
	InitialAttributes.Add(TestAttribute1, 2);
	InitialAttributes.Add(TestAttribute2, 3);
	TestCard->SetInitialAttributes(InitialAttributes);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddCardToPlayerCardPile(Model, Player.PlayerIndex, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Num Attributes"), Model.Cards[0].CardModel.Attributes.Num(), 2);
	TestEqual(TEXT("Attribute 1 Class"), Model.Cards[0].CardModel.Attributes[0].Attribute, TestAttribute1);
	TestEqual(TEXT("Attribute 1 Value"), Model.Cards[0].CardModel.Attributes[0].Value, 2);
	TestEqual(TEXT("Attribute 2 Class"), Model.Cards[0].CardModel.Attributes[1].Attribute, TestAttribute2);
	TestEqual(TEXT("Attribute 2 Value"), Model.Cards[0].CardModel.Attributes[1].Value, 3);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToPlayerCardPileSetsGameplayTagsTest, "CardGame.CardPileService.AddCardToPlayerCardPileSetsGameplayTags", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToPlayerCardPileSetsGameplayTagsTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	Player.PlayerCardPiles.Add(TestCardPile);
	Model.Players.Add(Player);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	const FGameplayTag TestTagA = CardGameCardPileServiceTest::FNativeGameplayTags::Get().TestTagA;
	const FGameplayTag TestTagB = CardGameCardPileServiceTest::FNativeGameplayTags::Get().TestTagB;

	FGameplayTagContainer TestGameplayTags;
	TestGameplayTags.AddTag(TestTagA);
	TestGameplayTags.AddTag(TestTagB);
	TestCard->SetInitialGameplayTags(TestGameplayTags);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.AddCardToPlayerCardPile(Model, Player.PlayerIndex, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestTrue(TEXT("Card Has Gameplay Tag A"), Model.Cards[0].CardModel.GameplayTags.HasTag(TestTagA));
	TestTrue(TEXT("Card Has Gameplay Tag A"), Model.Cards[0].CardModel.GameplayTags.HasTag(TestTagB));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToPlayerCardPileRaisesEventTest, "CardGame.CardPileService.AddCardToPlayerCardPileRaisesEvent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToPlayerCardPileRaisesEventTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	
	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	Player.PlayerCardPiles.Add(TestCardPile);
	Model.Players.Add(Player);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	FCardGameCardPileService CardPileService(RandomNumberProvider);

	CardGameCardPileServiceTest::FOnCardAddedToPlayerCardPileTestEventHandler TestEventHandler;
	CardPileService.OnCardAddedToPlayerCardPile.AddRaw(&TestEventHandler,
		&CardGameCardPileServiceTest::FOnCardAddedToPlayerCardPileTestEventHandler::OnCardAddedToPlayerCardPile);
	
	CardPileService.AddCardToPlayerCardPile(Model, Player.PlayerIndex, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Event Player Index"), TestEventHandler.PlayerIndex, Player.PlayerIndex);
	TestEqual(TEXT("Event Card Pile Class"), TestEventHandler.CardPileClass, TestCardPileClass);
	TestEqual(TEXT("Event Card Class"), TestEventHandler.Card.CardClass, TestCard);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveCardBetweenGlobalCardPilesRemovesCardFromOldPileTest, "CardGame.CardPileService.MoveCardBetweenGlobalCardPilesRemovesCardFromOldPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveCardBetweenGlobalCardPilesRemovesCardFromOldPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel MovedCard(0, TestCardClass);
	FCardGameCardModel UnchangedCard(1, TestCardClass);

	Model.Cards.Add(MovedCard);
	Model.Cards.Add(UnchangedCard);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard.InstanceId);
	OldCardPile.Cards.Add(UnchangedCard.InstanceId);
	Model.GlobalCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Model.GlobalCardPiles.Add(NewCardPile);

	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.MoveCardBetweenGlobalCardPiles(Model, OldCardPileClass, NewCardPileClass, MovedCard.InstanceId);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Remaining Card Instance Id"), Model.GlobalCardPiles[0].Cards[0], UnchangedCard.InstanceId);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveCardBetweenGlobalCardPilesAddsCardToNewPileTest, "CardGame.CardPileService.MoveCardBetweenGlobalCardPilesAddsCardToNewPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveCardBetweenGlobalCardPilesAddsCardToNewPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel MovedCard(0, TestCardClass);
	FCardGameCardModel UnchangedCard(1, TestCardClass);

	Model.Cards.Add(MovedCard);
	Model.Cards.Add(UnchangedCard);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard.InstanceId);
	OldCardPile.Cards.Add(UnchangedCard.InstanceId);
	Model.GlobalCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Model.GlobalCardPiles.Add(NewCardPile);

	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.MoveCardBetweenGlobalCardPiles(Model, OldCardPileClass, NewCardPileClass, MovedCard.InstanceId);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[1].Cards.Num(), 1);
	TestEqual(TEXT("New Card Instance Id"), Model.GlobalCardPiles[1].Cards[0], MovedCard.InstanceId);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveCardBetweenPlayerCardPilesRemovesCardFromOldPileTest, "CardGame.CardPileService.MoveCardBetweenPlayerCardPilesRemovesCardFromOldPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveCardBetweenPlayerCardPilesRemovesCardFromOldPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	
	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel MovedCard(0, TestCardClass);
	FCardGameCardModel UnchangedCard(1, TestCardClass);

	Model.Cards.Add(MovedCard);
	Model.Cards.Add(UnchangedCard);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard.InstanceId);
	OldCardPile.Cards.Add(UnchangedCard.InstanceId);
	Player.PlayerCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Player.PlayerCardPiles.Add(NewCardPile);

	Model.Players.Add(Player);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.MoveCardBetweenPlayerCardPiles(Model, Player.PlayerIndex, OldCardPileClass, NewCardPileClass, MovedCard.InstanceId);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Remaining Card Instance Id"), Model.Players[0].PlayerCardPiles[0].Cards[0], UnchangedCard.InstanceId);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveCardBetweenPlayerCardPilesAddsCardToNewPileTest, "CardGame.CardPileService.MoveCardBetweenPlayerCardPilesAddsCardToNewPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveCardBetweenPlayerCardPilesAddsCardToNewPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	
	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel MovedCard(0, TestCardClass);
	FCardGameCardModel UnchangedCard(1, TestCardClass);

	Model.Cards.Add(MovedCard);
	Model.Cards.Add(UnchangedCard);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard.InstanceId);
	OldCardPile.Cards.Add(UnchangedCard.InstanceId);
	Player.PlayerCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Player.PlayerCardPiles.Add(NewCardPile);

	Model.Players.Add(Player);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.MoveCardBetweenPlayerCardPiles(Model, Player.PlayerIndex, OldCardPileClass, NewCardPileClass, MovedCard.InstanceId);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[1].Cards.Num(), 1);
	TestEqual(TEXT("New Card Instance Id"), Model.Players[0].PlayerCardPiles[1].Cards[0], MovedCard.InstanceId);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveLastCardBetweenPlayerCardPilesRemovesCardFromOldPileTest, "CardGame.CardPileService.MoveLastCardBetweenPlayerCardPilesRemovesCardFromOldPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveLastCardBetweenPlayerCardPilesRemovesCardFromOldPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	
	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel UnchangedCard(0, TestCardClass);
	FCardGameCardModel MovedCard(1, TestCardClass);

	Model.Cards.Add(UnchangedCard);
	Model.Cards.Add(MovedCard);

	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(UnchangedCard.InstanceId);
	OldCardPile.Cards.Add(MovedCard.InstanceId);
	Player.PlayerCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Player.PlayerCardPiles.Add(NewCardPile);

	Model.Players.Add(Player);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.MoveLastCardBetweenPlayerCardPiles(Model, Player.PlayerIndex, OldCardPileClass, NewCardPileClass);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Remaining Card Instance Id"), Model.Players[0].PlayerCardPiles[0].Cards[0], UnchangedCard.InstanceId);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveLastCardBetweenPlayerCardPilesAddsCardToNewPileTest, "CardGame.CardPileService.MoveCardBetweenPlayerCardPilesAddsCardToNewPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveLastCardBetweenPlayerCardPilesAddsCardToNewPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 2;
	
	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel UnchangedCard(0, TestCardClass);
	FCardGameCardModel MovedCard(1, TestCardClass);

	Model.Cards.Add(UnchangedCard);
	Model.Cards.Add(MovedCard);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(UnchangedCard.InstanceId);
	OldCardPile.Cards.Add(MovedCard.InstanceId);
	Player.PlayerCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Player.PlayerCardPiles.Add(NewCardPile);

	Model.Players.Add(Player);
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(RandomNumberProvider);
	
	CardPileService.MoveLastCardBetweenPlayerCardPiles(Model, Player.PlayerIndex, OldCardPileClass, NewCardPileClass);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[1].Cards.Num(), 1);
	TestEqual(TEXT("New Card Instance Id"), Model.Players[0].PlayerCardPiles[1].Cards[0], MovedCard.InstanceId);
	return true;
}
