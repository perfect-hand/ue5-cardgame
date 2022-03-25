#include "Assets/CardGameConfiguration.h"

TArray<UCardGameCardPile*> UCardGameConfiguration::GetGlobalCardPileClasses() const
{
	return GlobalCardPileClasses;
}

void UCardGameConfiguration::SetGlobalCardPileClasses(TArray<UCardGameCardPile*> InGlobalCardPileClasses)
{
	GlobalCardPileClasses = InGlobalCardPileClasses;
}

TArray<UCardGameCardPile*> UCardGameConfiguration::GetPlayerCardPileClasses() const
{
	return PlayerCardPileClasses;
}

void UCardGameConfiguration::SetPlayerCardPileClasses(TArray<UCardGameCardPile*> InPlayerCardPileClasses)
{
	PlayerCardPileClasses = InPlayerCardPileClasses;
}
