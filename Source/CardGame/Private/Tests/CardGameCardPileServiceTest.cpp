#include "Misc/AutomationTest.h"

#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "Assets/CardGameConfiguration.h"
#include "Model/CardGameModel.h"
#include "Providers/CardGameCardInstanceIdProvider.h"
#include "Providers/CardGameRandomNumberProvider.h"
#include "Services/CardGameCardPileService.h"

namespace
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
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.AddGlobalCardPiles(Model, Configuration);
	
	// ASSERT
	TestEqual(TEXT("Num Global Card Piles"), Model.GlobalCardPiles.Num(), 2);
	TestEqual(TEXT("Global Card Pile 0"), Model.GlobalCardPiles[0].CardPileClass, TestCardPile0);
	TestEqual(TEXT("Global Card Pile 1"), Model.GlobalCardPiles[1].CardPileClass, TestCardPile1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToGlobalCardPileAssignsUniqueInstanceIdTest, "CardGame.CardPileService.AddCardToGlobalCardPileAssignsUniqueInstanceId", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToGlobalCardPileAssignsUniqueInstanceIdTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	UCardGameCardPile* TestCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel TestCardPile;
	TestCardPile.CardPileClass = TestCardPileClass;
	Model.GlobalCardPiles.Add(TestCardPile);

	UCardGameCard* TestCard = NewObject<UCardGameCard>();
	
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	CardInstanceIdProvider.NewId();
	CardInstanceIdProvider.NewId();
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Card Instance Id"), Model.GlobalCardPiles[0].Cards[0].InstanceId, 3LL);
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
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Card Class"), Model.GlobalCardPiles[0].Cards[0].CardClass, TestCard);
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
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);

	FOnCardAddedToGlobalCardPileTestEventHandler TestEventHandler;
	CardPileService.OnCardAddedToGlobalCardPile.AddRaw(&TestEventHandler, &FOnCardAddedToGlobalCardPileTestEventHandler::OnCardAddedToGlobalCardPile);
	
	CardPileService.AddCardToGlobalCardPile(Model, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Event Card Pile Class"), TestEventHandler.CardPileClass, TestCardPileClass);
	TestEqual(TEXT("Event Card Class"), TestEventHandler.Card.CardClass, TestCard);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddCardToPlayerCardPileAssignsUniqueInstanceIdTest, "CardGame.CardPileService.AddCardToPlayerCardPileAssignsUniqueInstanceId", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddCardToPlayerCardPileAssignsUniqueInstanceIdTest::RunTest(const FString& Parameters)
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
	
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	CardInstanceIdProvider.NewId();
	CardInstanceIdProvider.NewId();
	
	// ACT
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.AddCardToPlayerCardPile(Model, Player.PlayerIndex, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Card Instance Id"), Model.Players[0].PlayerCardPiles[0].Cards[0].InstanceId, 3LL);
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
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.AddCardToPlayerCardPile(Model, Player.PlayerIndex, TestCardPileClass, TestCard);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Card Class"), Model.Players[0].PlayerCardPiles[0].Cards[0].CardClass, TestCard);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveCardBetweenGlobalCardPilesRemovesCardFromOldPileTest, "CardGame.CardPileService.MoveCardBetweenGlobalCardPilesRemovesCardFromOldPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveCardBetweenGlobalCardPilesRemovesCardFromOldPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel MovedCard(1, TestCardClass);
	FCardGameCardModel UnchangedCard(2, TestCardClass);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard);
	OldCardPile.Cards.Add(UnchangedCard);
	Model.GlobalCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Model.GlobalCardPiles.Add(NewCardPile);

	// ACT
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.MoveCardBetweenGlobalCardPiles(Model, OldCardPileClass, NewCardPileClass, 0);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Remaining Card Instance Id"), Model.GlobalCardPiles[0].Cards[0].InstanceId, UnchangedCard.InstanceId);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMoveCardBetweenGlobalCardPilesAddsCardToNewPileTest, "CardGame.CardPileService.MoveCardBetweenGlobalCardPilesAddsCardToNewPile", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FMoveCardBetweenGlobalCardPilesAddsCardToNewPileTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	UCardGameCard* TestCardClass = NewObject<UCardGameCard>();

	FCardGameCardModel MovedCard(1, TestCardClass);
	FCardGameCardModel UnchangedCard(2, TestCardClass);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard);
	OldCardPile.Cards.Add(UnchangedCard);
	Model.GlobalCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Model.GlobalCardPiles.Add(NewCardPile);

	// ACT
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.MoveCardBetweenGlobalCardPiles(Model, OldCardPileClass, NewCardPileClass, 0);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.GlobalCardPiles[1].Cards.Num(), 1);
	TestEqual(TEXT("New Card Instance Id"), Model.GlobalCardPiles[1].Cards[0].InstanceId, MovedCard.InstanceId);
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

	FCardGameCardModel MovedCard(1, TestCardClass);
	FCardGameCardModel UnchangedCard(2, TestCardClass);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard);
	OldCardPile.Cards.Add(UnchangedCard);
	Player.PlayerCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Player.PlayerCardPiles.Add(NewCardPile);

	Model.Players.Add(Player);
	
	// ACT
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.MoveCardBetweenPlayerCardPiles(Model, Player.PlayerIndex, OldCardPileClass, NewCardPileClass, 0);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[0].Cards.Num(), 1);
	TestEqual(TEXT("Remaining Card Instance Id"), Model.Players[0].PlayerCardPiles[0].Cards[0].InstanceId, UnchangedCard.InstanceId);
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

	FCardGameCardModel MovedCard(1, TestCardClass);
	FCardGameCardModel UnchangedCard(2, TestCardClass);
	
	UCardGameCardPile* OldCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel OldCardPile;
	OldCardPile.CardPileClass = OldCardPileClass;
	OldCardPile.Cards.Add(MovedCard);
	OldCardPile.Cards.Add(UnchangedCard);
	Player.PlayerCardPiles.Add(OldCardPile);

	UCardGameCardPile* NewCardPileClass = NewObject<UCardGameCardPile>();
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = NewCardPileClass;
	Player.PlayerCardPiles.Add(NewCardPile);

	Model.Players.Add(Player);
	
	// ACT
	FCardGameCardInstanceIdProvider CardInstanceIdProvider;
	FCardGameRandomNumberProvider RandomNumberProvider;
	const FCardGameCardPileService CardPileService(CardInstanceIdProvider, RandomNumberProvider);
	
	CardPileService.MoveCardBetweenPlayerCardPiles(Model, Player.PlayerIndex, OldCardPileClass, NewCardPileClass, 0);
	
	// ASSERT
	TestEqual(TEXT("Num Cards"), Model.Players[0].PlayerCardPiles[1].Cards.Num(), 1);
	TestEqual(TEXT("New Card Instance Id"), Model.Players[0].PlayerCardPiles[1].Cards[0].InstanceId, MovedCard.InstanceId);
	return true;
}
