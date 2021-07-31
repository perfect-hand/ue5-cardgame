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
