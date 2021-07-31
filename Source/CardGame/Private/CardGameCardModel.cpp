#include "CardGameCardModel.h"

FCardGameCardModel::FCardGameCardModel()
{
	CardClass = nullptr;
}

FCardGameCardModel::FCardGameCardModel(int64 InInstanceId, UCardGameCard* InCardClass)
{
	InstanceId = InInstanceId;
	CardClass = InCardClass;
}

int64 FCardGameCardModel::GetInstanceId() const
{
	return InstanceId;
}

UCardGameCard* FCardGameCardModel::GetCardClass() const
{
	return CardClass;
}
