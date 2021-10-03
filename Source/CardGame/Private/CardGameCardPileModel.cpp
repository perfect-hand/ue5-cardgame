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

FCardGameCardModel FCardGameCardPileModel::AddCard(int64 InstanceId, UCardGameCard* CardClass)
{
	const FCardGameCardModel NewCard(InstanceId, CardClass);
	AddCard(NewCard);
	return NewCard;
}

void FCardGameCardPileModel::AddCard(FCardGameCardModel Card)
{
	Cards.Add(Card);
}

FCardGameCardModel FCardGameCardPileModel::GetCard(int32 Index) const
{
	return Cards[Index];
}

void FCardGameCardPileModel::RemoveCard(int32 Index)
{
	Cards.RemoveAt(Index);
}

void FCardGameCardPileModel::Shuffle(FRandomStream& RandomStream)
{
	TArray<FCardGameCardModel> ShuffledCards;

	while (!Cards.IsEmpty())
	{
		int32 RandomIndex = RandomStream.RandHelper(Cards.Num());
		ShuffledCards.Add(Cards[RandomIndex]);
		Cards.RemoveAt(RandomIndex);
	}

	Cards = ShuffledCards;
}

const TArray<FCardGameCardModel>& FCardGameCardPileModel::GetCards() const
{
	return Cards;
}
