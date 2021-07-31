#include "CardGamePlayerModel.h"

int32 FCardGamePlayerModel::GetPlayerIndex() const
{
	return PlayerIndex;
}

void FCardGamePlayerModel::SetPlayerIndex(int32 InPlayerIndex)
{
	PlayerIndex = InPlayerIndex;
}

void FCardGamePlayerModel::AddCardPile(UCardGameCardPile* CardPileClass)
{
	FCardGameCardPileModel NewCardPile;
	NewCardPile.SetCardPileClass(CardPileClass);
	PlayerCardPiles.Add(NewCardPile);
}
