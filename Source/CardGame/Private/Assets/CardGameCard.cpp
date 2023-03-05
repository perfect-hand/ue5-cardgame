#include "Assets/CardGameCard.h"

FText UCardGameCard::GetCardName() const
{
	return CardName;
}

const TMap<UCardGameAttribute*, int32>& UCardGameCard::GetInitialAttributes() const
{
	return InitialAttributes;
}

void UCardGameCard::SetInitialAttributes(const TMap<UCardGameAttribute*, int32>& InInitialAttributes)
{
	InitialAttributes = InInitialAttributes;
}

const FGameplayTagContainer& UCardGameCard::GetInitialGameplayTags() const
{
	return InitialGameplayTags;
}

void UCardGameCard::SetInitialGameplayTags(const FGameplayTagContainer& InInitialGameplayTags)
{
	InitialGameplayTags = InInitialGameplayTags;
}
