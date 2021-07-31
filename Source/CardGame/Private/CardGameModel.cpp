#include "CardGameModel.h"

void FCardGameModel::AddPlayer(int32 PlayerIndex, TArray<TSubclassOf<UCardGameCardPile>> CardPileClasses)
{
	FCardGamePlayerModel NewPlayer;
	NewPlayer.SetPlayerIndex(PlayerIndex);

	for (const TSubclassOf<UCardGameCardPile> CardPileClass : CardPileClasses)
	{
		NewPlayer.AddCardPile(CardPileClass);
	}

	Players.Add(NewPlayer);
}
