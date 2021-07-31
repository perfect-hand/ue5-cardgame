#include "CardGameModel.h"

void FCardGameModel::AddPlayer(int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses)
{
	FCardGamePlayerModel NewPlayer;
	NewPlayer.SetPlayerIndex(PlayerIndex);

	for (UCardGameCardPile* CardPileClass : CardPileClasses)
	{
		NewPlayer.AddCardPile(CardPileClass);
	}

	Players.Add(NewPlayer);
}

void FCardGameModel::AddCardToPlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.AddCardToCardPile(CardPileClass, CardClass, CardInstanceIdPool);
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

void FCardGameModel::MoveCardBetweenPlayerCardPiles(int32 PlayerIndex, UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.MoveCardBetweenPiles(From, To, CardIndex);
			return;
		}
	}
}
