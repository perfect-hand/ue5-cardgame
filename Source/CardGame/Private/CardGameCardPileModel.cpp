#include "CardGameCardPileModel.h"

FCardGameCardPileModel::FCardGameCardPileModel()
{
	CardPileClass = nullptr;
}

UCardGameCardPile* FCardGameCardPileModel::GetCardPileClass() const
{
	return CardPileClass;
}

void FCardGameCardPileModel::SetCardPileClass(UCardGameCardPile* InCardPileClass)
{
	CardPileClass = InCardPileClass;
}

void FCardGameCardPileModel::AddCard(int64 InstanceId, UCardGameCard* CardClass)
{
	const FCardGameCardModel NewCard(InstanceId, CardClass);
	Cards.Add(NewCard);
}
