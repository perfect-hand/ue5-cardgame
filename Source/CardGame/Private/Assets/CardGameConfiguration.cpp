#include "Assets/CardGameConfiguration.h"

TArray<UCardGameCardPile*> UCardGameConfiguration::GetGlobalCardPileClasses() const
{
	return GlobalCardPileClasses;
}

TArray<UCardGameCardPile*> UCardGameConfiguration::GetPlayerCardPileClasses() const
{
	return PlayerCardPileClasses;
}
