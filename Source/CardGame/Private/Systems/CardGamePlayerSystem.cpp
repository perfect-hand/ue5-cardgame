#include "Systems/CardGamePlayerSystem.h"

#include "CardGameCardPile.h"
#include "Model/CardGameCardPileModel.h"
#include "Model/CardGameModel.h"
#include "Model/CardGamePlayerModel.h"

void FCardGamePlayerSystem::AddPlayer(FCardGameModel& Model, int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses) const
{
	FCardGamePlayerModel NewPlayer;
	NewPlayer.PlayerIndex = PlayerIndex;

	for (UCardGameCardPile* CardPileClass : CardPileClasses)
	{
		FCardGameCardPileModel NewCardPile;
		NewCardPile.CardPileClass = CardPileClass;
		NewPlayer.PlayerCardPiles.Add(NewCardPile);
	}

	Model.Players.Add(NewPlayer);
}
