#include "CardGameModel.h"

void FCardGameModel::AddPlayer(int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses)
{
	FCardGamePlayerModel NewPlayer;
	NewPlayer.SetPlayerIndex(PlayerIndex);

	for (UCardGameCardPile* CardPileClass : CardPileClasses)
	{
		NewPlayer.AddCardPile(CardPileClass);
	}

	NewPlayer.SetCardInstanceIdPool(CardInstanceIdPool);
	Players.Add(NewPlayer);
}

void FCardGameModel::AddCardToPlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.AddCardToCardPile(CardPileClass, CardClass);
			return;
		}
	}
}

void FCardGameModel::ShufflePlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.ShuffleCardPile(CardPileClass, RandomStream);
			return;
		}
	}
}
