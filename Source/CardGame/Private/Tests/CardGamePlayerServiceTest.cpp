#include "Misc/AutomationTest.h"

#include "Assets/CardGameCardPile.h"
#include "Assets/CardGameConfiguration.h"
#include "Model/CardGameModel.h"
#include "Services/CardGamePlayerService.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddPlayerUsesUniquePlayerIndexTest, "CardGame.PlayerService.AddPlayerUsesUniquePlayerIndex", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddPlayerUsesUniquePlayerIndexTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	
	FCardGamePlayerModel ExistingPlayer0;
	ExistingPlayer0.PlayerIndex = 0;
	Model.Players.Add(ExistingPlayer0);
	
	FCardGamePlayerModel ExistingPlayer1;
	ExistingPlayer1.PlayerIndex = 1;
	Model.Players.Add(ExistingPlayer1);
	
	// ACT
	constexpr FCardGamePlayerService PlayerService;
	const int32 NewPlayerIndex = PlayerService.AddPlayer(Model, nullptr);
	
	// ASSERT
	TestEqual(TEXT("Num Players"), Model.Players.Num(), 3);
	TestEqual(TEXT("New Player Index"), Model.Players[2].PlayerIndex, 2);
	TestEqual(TEXT("Returned Player Index"), NewPlayerIndex, 2);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddPlayerAddsPlayerCardPilesTest, "CardGame.PlayerService.AddPlayerAddsPlayerCardPiles", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FAddPlayerAddsPlayerCardPilesTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;

	UCardGameCardPile* TestCardPile0 = NewObject<UCardGameCardPile>();
	UCardGameCardPile* TestCardPile1 = NewObject<UCardGameCardPile>();
	
	TArray<UCardGameCardPile*> CardPileClasses;
	CardPileClasses.Add(TestCardPile0);
	CardPileClasses.Add(TestCardPile1);
	
	UCardGameConfiguration* Configuration = NewObject<UCardGameConfiguration>();
	Configuration->SetPlayerCardPileClasses(CardPileClasses);
	
	// ACT
	constexpr FCardGamePlayerService PlayerService;
	PlayerService.AddPlayer(Model, Configuration);
	
	// ASSERT
	TestEqual(TEXT("Num Players"), Model.Players.Num(), 1);
	TestEqual(TEXT("Num Player Card Piles"), Model.Players[0].PlayerCardPiles.Num(), 2);
	TestEqual(TEXT("Player Card Pile 0"), Model.Players[0].PlayerCardPiles[0].CardPileClass, TestCardPile0);
	TestEqual(TEXT("Player Card Pile 1"), Model.Players[0].PlayerCardPiles[1].CardPileClass, TestCardPile1);
	return true;
}
