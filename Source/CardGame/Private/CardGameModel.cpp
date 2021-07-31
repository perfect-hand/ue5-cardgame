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
