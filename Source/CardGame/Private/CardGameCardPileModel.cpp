#include "CardGameCardPileModel.h"

TSubclassOf<UCardGameCardPile> FCardGameCardPileModel::GetCardPileClass() const
{
	return CardPileClass;
}

void FCardGameCardPileModel::SetCardPileClass(TSubclassOf<UCardGameCardPile> InCardPileClass)
{
	CardPileClass = InCardPileClass;
}
