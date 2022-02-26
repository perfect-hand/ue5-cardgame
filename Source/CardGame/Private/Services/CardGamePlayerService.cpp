#include "Services/CardGamePlayerService.h"

#include "Assets/CardGameCardPile.h"
#include "Model/CardGameCardPileModel.h"
#include "Model/CardGameModel.h"
#include "Model/CardGamePlayerModel.h"

void FCardGamePlayerService::AddPlayer(FCardGameModel& Model, int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses) const
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
