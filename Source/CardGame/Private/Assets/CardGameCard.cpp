#include "Assets/CardGameCard.h"

FText UCardGameCard::GetCardName() const
{
	return CardName;
}

const TMap<UCardGameAttribute*, int32>& UCardGameCard::GetInitialAttributes() const
{
	return InitialAttributes;
}

const FGameplayTagContainer& UCardGameCard::GetInitialGameplayTags() const
{
	return InitialGameplayTags;
}
