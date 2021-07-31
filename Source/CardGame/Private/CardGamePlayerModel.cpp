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

void FCardGamePlayerModel::AddCardToCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass,
	FCardGameCardInstanceIdPool& CardInstanceIdPool)
{
	FCardGameCardPileModel* CardPile = GetCardPile(CardPileClass);

	if (!CardPile)
	{
		return;
	}
	
	int64 NewCardInstanceId = CardInstanceIdPool.NewId();
	CardPile->AddCard(NewCardInstanceId, CardClass);
	
	UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to %s of player %d."),
		*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName(), PlayerIndex);
}

void FCardGamePlayerModel::ShuffleCardPile(UCardGameCardPile* CardPileClass, FRandomStream& RandomStream)
{
	FCardGameCardPileModel* CardPile = GetCardPile(CardPileClass);

	if (!CardPile)
	{
		return;
	}
	
	CardPile->Shuffle(RandomStream);
	
	UE_LOG(LogCardGame, Log, TEXT("Shuffled %s of player %d."), *CardPileClass->GetName(), PlayerIndex);
}

void FCardGamePlayerModel::MoveCardBetweenPiles(UCardGameCardPile* From, UCardGameCardPile* To, int32 Index)
{
	FCardGameCardPileModel* FromCardPile = GetCardPile(From);
	FCardGameCardPileModel* ToCardPile = GetCardPile(To);
	
	if (!FromCardPile || !ToCardPile)
	{
		return;
	}

	FCardGameCardModel Card = FromCardPile->GetCard(Index);
	ToCardPile->AddCard(Card);
	FromCardPile->RemoveCard(Index);

	UE_LOG(LogCardGame, Log, TEXT("Moved %s (%d) of player %d from %s to %s."), *Card.GetCardClass()->GetName(),
		Card.GetInstanceId(), PlayerIndex, *From->GetName(), *To->GetName());
}

FCardGameCardPileModel* FCardGamePlayerModel::GetCardPile(UCardGameCardPile* CardPileClass)
{
	for (FCardGameCardPileModel& CardPile : PlayerCardPiles)
	{
		if (CardPile.GetCardPileClass() == CardPileClass)
		{
			return &CardPile;
		}
	}

	return nullptr;
}
