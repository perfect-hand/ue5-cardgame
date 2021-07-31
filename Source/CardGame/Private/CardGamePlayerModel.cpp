#include "CardGamePlayerModel.h"

#include "CardGameCard.h"
#include "CardGameCardPile.h"
#include "CardGameLogCategory.h"

uint8 FCardGamePlayerModel::GetPlayerIndex() const
{
	return PlayerIndex;
}

void FCardGamePlayerModel::SetPlayerIndex(uint8 InPlayerIndex)
{
	PlayerIndex = InPlayerIndex;
}

void FCardGamePlayerModel::AddCardPile(UCardGameCardPile* CardPileClass)
{
	FCardGameCardPileModel NewCardPile;
	NewCardPile.SetCardPileClass(CardPileClass);
	PlayerCardPiles.Add(NewCardPile);
}

void FCardGamePlayerModel::AddCardToCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	for (FCardGameCardPileModel& CardPile : PlayerCardPiles)
	{
		if (CardPile.GetCardPileClass() == CardPileClass)
		{
			int64 NewCardInstanceId = CardInstanceIdPool.NewId();
			CardPile.AddCard(NewCardInstanceId, CardClass);
			UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to %s of player %d."),
				*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName(), PlayerIndex);
			return;
		}
	}
}

void FCardGamePlayerModel::SetCardInstanceIdPool(FCardGameCardInstanceIdPool& InCardInstanceIdPool)
{
	CardInstanceIdPool = InCardInstanceIdPool;
}
